from django.contrib.auth import logout, authenticate, login
from django.http import HttpResponseRedirect
from django.shortcuts import render, get_object_or_404

from django.http import HttpResponse

from django.core.paginator import Paginator, EmptyPage, PageNotAnInteger

from ask.forms import SignUpForm, LoginForm
from models import *


# from django.views.decorators.cache import cache_page

# @cache_page(600 * 15)
def paginate(objects_list, request):
    paginator = Paginator(objects_list, 5)  # Show 5 contacts per page

    page = request.GET.get('page')
    try:
        objects_page = paginator.page(page)
    except PageNotAnInteger:
        # If page is not an integer, deliver first page.
        objects_page = paginator.page(1)
    except EmptyPage:
        # If page is out of range (e.g. 9999), deliver last page of results.
        objects_page = paginator.page(paginator.num_pages)

    return objects_page, paginator


def basewsgi(request):
    gett = ''
    for key, value in request.GET.iteritems():
        gett = key + '=' + value + '<br>' + gett
    postt = ''
    for key in request.POST:
        postt = key + '=' + request.POST[key] + '<br>' + postt
    a = 'Request method: ' + request.method + '<br />GET params:<br> ' + gett + '<br /> POST params: ' + '<br />' + postt + '\n'
    return HttpResponse(a)


def index(request):
    questions = Question.objects.top()
    objects_page, paginator = paginate(questions, request)
    return render(request, 'index.html', {
        "questions": objects_page,
        'atags': Tag.objects.all()
    })


def bytag(request, tag):
    questions = Question.objects.by_tag(tag)
    objects_page, paginator = paginate(questions, request)
    return render(request, 'bytag.html', {
        "questions": objects_page,
        'tag' : tag,
        'atags': Tag.objects.all()
    })


def ask(request):
    return render(request, 'ask.html')


def hot(request):
    questions = Question.objects.top()
    objects_page, paginator = paginate(questions, request)
    return render(request, 'hot.html', {
        "questions": objects_page,
    })


def login_to_system(request):
    if request.user.is_authenticated:
        return HttpResponseRedirect( '/' )

    if(request.method == "POST"):
        login_name = request.POST['login']
        password = request.POST['password']
        user = authenticate(username = login_name, password = password)
        if user:
            login(request, user)
            return HttpResponseRedirect('/')
        else:
            return HttpResponseRedirect('/login?error=1')
    else:
        form = LoginForm()

    return render(request, 'login.html', {
        'form': form
    })


def signup(request):
    if(request.method == "POST"):
        form = SignUpForm(request.POST, request.FILES)
        if form.is_valid() and form.clean():
            form.save()

            return HttpResponseRedirect('/')

        #print(form.cleaned_data)
    else:
        form = SignUpForm()

    return render(request, 'register.html', {
        'form': form
    })

def logout_user(request):
    if not request.user.is_authenticated:
       return HttpResponseRedirect('/')
    logout(request)
    return HttpResponseRedirect('/')

def question(request, question_id):
    q = get_object_or_404(Question, id=question_id)
    answers = Answer.objects.filter_question(q)
    #form = AnswerForm(initial={'question': str(pk)})
    return render(request, 'question.html', {
        'question': q,
        'answers': answers,
        'atags' : Tag.objects.all()
        #'form': form,
    })
