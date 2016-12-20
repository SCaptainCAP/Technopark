from django.shortcuts import render

from django.http import HttpResponse

from django.core.paginator import Paginator, EmptyPage, PageNotAnInteger

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
    questions = Question.questionManager.all()
    objects_page, paginator = paginate(questions, request)
    return render(request, 'main.html', {
        "questions": objects_page,
    })


def bytag(request):
    questions = []
    for i in xrange(1, 5):
        questions.append({
            'title': 'title ' + str(i),
            'id': i,
            'text': 'text' + str(i),
        })

    return render(request, 'bytag.html', {
        "questions": questions,
    })


def ask(request):
    return render(request, 'ask.html')


def hot(request):
    return render(request, 'hot.html')


def login(request):
    return render(request, 'login.html')


def signup(request):
    return render(request, 'register.html')


def question(request, question_id):
    return render(request, 'question.html')
