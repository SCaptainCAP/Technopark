"""ask_govjazin URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/1.10/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  url(r'^$', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  url(r'^$', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.conf.urls import url, include
    2. Add a URL to urlpatterns:  url(r'^blog/', include('blog.urls'))
"""
from django.conf.urls import url
from django.contrib import admin

from ask import views

urlpatterns = [
    url(r'^admin/?', admin.site.urls),
    url(r'^basewsgi/?', views.basewsgi, name='basewsgi'),
    url(r'^hot/?', views.hot, name='hot'),
    url(r'^ask/?', views.ask, name='ask'),
    url(r'^login/?', views.login_to_system, name='login'),
    url(r'^signup/?', views.signup, name='signup'),
    url(r'^settings/?', views.settings, name='settings'),
    url(r'^logout/?', views.logout_user, name='logout'),
    url(r'^tag/(?P<tag>.+)/?', views.bytag, name='tag'),
    url(r'^question/(?P<question_id>[0-9]+)/?', views.question, name='question'),
    url(r'^likeanswer/?', views.like_answer, name='likeanswer'),
    url(r'^dislikeanswer/?', views.dislike_answer, name='dislikeanswer'),
    url(r'^like/?', views.like_question, name='like'),
    url(r'^dislike/?', views.dislike_question, name='dislike'),
    url(r'^setanswercorrect/?', views.set_answer_correct, name='setanswercorrect'),
    url(r'^$', views.index, name='index'),
]
