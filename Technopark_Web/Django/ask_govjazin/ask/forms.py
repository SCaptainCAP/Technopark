import os
import re
from django.contrib.auth.models import User
from django.contrib.auth.password_validation import password_validators_help_text_html
from django.core.mail import send_mail

from models import *

from django import forms


# from locals_settings import *

# def is_spam(data):
#     return True

class RegisterForm(forms.Form):
    email = forms.EmailField(
        label='Email',
        max_length=100, )
    name = forms.CharField(
        label='Login',
        max_length=100,
        required=True, )
    password = forms.CharField(
        label='Password',
        widget=forms.PasswordInput(),
        required=True, )
    password_again = forms.CharField(
        label='Repeat password',
        widget=forms.PasswordInput(),
        required=True, )

    image = forms.ImageField(
        label='Avatar',
        required=False
    )

    def clean(self):
        password = self.cleaned_data.get('password', None)
        rpassword = self.cleaned_data.get('password_again', None)
        username = self.cleaned_data.get('name', None)
        email = self.cleaned_data.get('email', None)
        if not email or not password or not rpassword or not username:
            raise forms.ValidationError(u'Please fill all required fields')
        if User.objects.filter(email=email).exists():
            raise forms.ValidationError(u'Email "%s" is already in use.' % email)
        if User.objects.filter(username=username).exists():
            raise forms.ValidationError(u'Username "%s" is already in use.' % username)
        if password != rpassword:
            raise forms.ValidationError(u'Passwords must equal')
        return self.cleaned_data

    def create_account(self):
        data = self.data
        user = User.objects.create_user(username=data['name'], email=data['email'], password=data['password'])
        image = self.cleaned_data.get('image', None)
        if (image):
            profile = Profile(user=user, avatar=image)
        else:
            profile = Profile(user=user)
        profile.save()


class SettingsForm(forms.Form):
    email = forms.EmailField(
        label='Email',
        max_length=100, )
    name = forms.CharField(
        label='Login',
        max_length=100,
        required=True, )
    password = forms.CharField(
        label='Password',
        widget=forms.PasswordInput(),
        required=False, )
    password_again = forms.CharField(
        label='Repeat password',
        widget=forms.PasswordInput(),
        required=False, )

    image = forms.ImageField(
        label='Avatar',
        required=False,
    )

    def __init__(self, *args, **kwargs):
        self.user = kwargs.pop('user', None)
        super(SettingsForm, self).__init__(*args, **kwargs)

    def clean(self):
        password = self.cleaned_data.get('password', None)
        rpassword = self.cleaned_data.get('password_again', None)
        username = self.cleaned_data.get('name', None)
        email = self.cleaned_data.get('email', None)
        if not email or not username:
            raise forms.ValidationError(u'Some fields need to be filled')
        f1 = User.objects.filter(email=email)
        if f1.exists() and not f1[0] == self.user:
            raise forms.ValidationError(u'Email "%s" is already in use.' % email)
        f2 = User.objects.filter(username=username)
        if f2.exists() and not f2[0] == self.user:
            raise forms.ValidationError(u'Username "%s" is already in use.' % username)
        if password:
            if not rpassword or not password == rpassword:
                raise forms.ValidationError(u'Passwords must equal')
        return self.cleaned_data

    def update_account(self):
        password = self.cleaned_data.get('password', None)
        username = self.cleaned_data.get('name', None)
        email = self.cleaned_data.get('email', None)
        image = self.cleaned_data.get('image', None)
        profile = Profile.objects.by_user(self.user)
        if (password):
            profile.user.password = password
        if (username):
            profile.user.username = username
        if (email):
            profile.user.email = email
        if image is None:  # nothing happened
            pass
        elif image:  # set new avatar
            if os.path.isfile(profile.avatar.path) and profile.avatar.path != (BASE_DIR + '/static/img/no-avatar.png'):
                os.remove(profile.avatar.path)
            profile.avatar = image
        else:  # clear
            if os.path.isfile(profile.avatar.path):
                os.remove(profile.avatar.path)
            profile.avatar = 'static/img/no-avatar.png'
        profile.user.save()
        profile.save()


class LoginForm(forms.Form):
    login = forms.CharField(
        widget=forms.TextInput,
        label="Login",
        required=True
    )
    password = forms.CharField(
        widget=forms.PasswordInput(),
        label="Password",
        required=True
    )

    def clean(self):
        password = self.cleaned_data.get('password', None)
        username = self.cleaned_data.get('login', None)
        if not password or not username:
            raise forms.ValidationError(u'Please fill all required fields')
        if not User.objects.filter(username=username).exists():
            raise forms.ValidationError(u'Username "%s" does not exist' % username)
        return self.cleaned_data


class CreateAnswerForm(forms.Form):
    text = forms.CharField(
        widget=forms.Textarea,
        label="Create your own answer",
        required=True
    )

    def __init__(self, *args, **kwargs):
        self.question = kwargs.pop('question', None)
        self.user = kwargs.pop('user', None)
        super(CreateAnswerForm, self).__init__(*args, **kwargs)

    def clean(self):
        text = self.cleaned_data.get('text', None)
        if not text:
            raise forms.ValidationError(u'You need to enter your answer')
        return self.cleaned_data

    def create_question(self):
        answer = Answer(text=self.cleaned_data.get('text', None), question=self.question, author=Profile.objects.by_user(self.user))
        try:
            send_mail('You have new answer!',
                  self.cleaned_data.get('text', None)+'| checkout it here: http://scaptaincap.asuscomm.com/question/' + str(self.question.id),
                  'mailer@scaptaincap.asuscomm.com',
                  [self.question.author.user.email], fail_silently=False)
        except:
            pass
        answer.save()


class MakeQuestionForm(forms.Form):
    title = forms.CharField(
        max_length=100,
        label="Title",
        required=True
    )
    text = forms.CharField(
        widget=forms.Textarea,
        label="Text",
        required=True
    )
    tags = forms.CharField(
        label="Tags",
        required=False
    )

    def clean(self):
        title = self.cleaned_data.get('title', None)
        text = self.cleaned_data.get('text', None)
        tags = self.cleaned_data.get('tags', None)
        if not title or not text:
            raise forms.ValidationError(u'Please fill all required fields')
        if tags:
            tags_text = tags.split(',')
            i = 0
            while i < len(tags_text):
                tags_text[i] = tags_text[i].strip()
                if len(tags_text[i]) > 20:
                    raise forms.ValidationError(u'Tag cannot be bigger than 20 symbols')
                if tags_text[i] == '':
                    tags_text.pop(i)
                    i -= 1
                i += 1
            if len(tags_text) > 3:
                raise forms.ValidationError(u'There can be no more than 3 tags')

        return self.cleaned_data

    def save(self, request):
        data = self.data
        tags_text = data['tags'].split(',')
        i = 0
        while i < len(tags_text):
            tags_text[i] = tags_text[i].strip()
            if tags_text[i] == '':
                tags_text.pop(i)
                i -= 1
            i += 1
        for i in tags_text:
            i.strip()
        tags_objs = []
        for tag in tags_text:
            tag_obj = Tag.objects.get_or_create(data=tag)[0]
            tag_obj.save()
            tags_objs.append(tag_obj)
        q = Question(title=data['title'], text=data['text'], author=Profile.objects.by_user(request.user))
        q.save()
        q.tags = tags_objs
        q.save()
        return q.id
