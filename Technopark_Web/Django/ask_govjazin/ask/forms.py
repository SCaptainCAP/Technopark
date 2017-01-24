from django.contrib.auth.models import User
from models import *

from django import forms

# from locals_settings import *

# def is_spam(data):
#     return True

class SignUpForm(forms.Form):
    email = forms.EmailField(
        label='Email',
        max_length=100,)
    name = forms.CharField(
        label='Login',
        max_length=100,
        required=True,)
    password = forms.CharField(
        label='Password',
        widget=forms.PasswordInput(),
        required=True,)
    password_again = forms.CharField(
        label='Repeat password',
        widget=forms.PasswordInput(),
        required=True,)

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
        if self.cleaned_data.get('password') != self.cleaned_data.get('password_again'):
            raise forms.ValidationError(u'Passwords must equal')
        return self.cleaned_data

    def save(self):
        data = self.data
        user = User.objects.create_user(username=data['name'], email=data['email'], password=data['password'])
        image = self.cleaned_data.get('image', None)
        if (image):
            profile = Profile(user=user, avatar=image)
        else:
            profile = Profile(user=user)
        profile.save()


class LoginForm(forms.Form):
    login = forms.CharField(widget = forms.TextInput)
    password = forms.CharField(widget=forms.PasswordInput(), label="Password")

    def is_valid(self):
        return super(LoginForm, self).is_valid()

# class ArticleForm(forms.ModelForm):
#     class Meta:
#         # model = Post
#         fields = ['titile' ] # ???
#
# class FeedbackForm(forms.Form):
#     email = forms.EmailField(max_length = 100)
#     message = forms.CharField(widget = forms.Textarea)
#
#     '''
#     def clean(self):
#         if is_spam(self.cleaned_data):
#             raise forms.ValidationError(
#                 'It is spam',
#                 code = 'spam'
#             )
#     '''
#
#
# class AddPostForm(forms.Form):
#     title = forms.EmailField(max_length = 100)
#     message = forms.CharField(widget = forms.Textarea)
#
#     image = forms.ImageField()
#
#     def __init__(self, user, **kwargs):
#         pass
#
#     def clean(self):
#         if is_spam(self.cleaned_data):
#             raise forms.ValidationError(
#                 u'It is spam',
#                 code = 'spam'
#             )
#
#     def save(self):
#         # post = Post(**self.cleaned_data)
#         # post.save()
#         #post = ""
#         return True
