from django.contrib.auth.models import User
from models import *

from django import forms

# from locals_settings import *

# def is_spam(data):
#     return True

class SignUpForm(forms.Form):
    name = forms.CharField(widget = forms.TextInput)
    email = forms.EmailField()

    password = forms.CharField(widget = forms.PasswordInput())
    repeat_password = forms.CharField(widget = forms.PasswordInput())

    image = forms.ImageField()

    def clean(self):
        #print(self.data['password'], self.data['repeat_password'])
        return self.data['password'] == self.data['repeat_password']

    def save(self):
        data = self.data
        #print("Test")
        #print(data)
        user = User.objects.create_user(username  = data['name'], email = data['email'], password = data['password'])
        profile = Profile(user = user)

        profile.save()


class LoginForm(forms.Form):
    login = forms.CharField(widget = forms.TextInput)
    password = forms.CharField(widget=forms.PasswordInput(), label="Password")

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
