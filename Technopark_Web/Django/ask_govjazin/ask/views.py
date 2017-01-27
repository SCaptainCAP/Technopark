from django.contrib.auth import logout, authenticate, login
from django.http import HttpResponseRedirect
from django.http import JsonResponse
from django.shortcuts import render, get_object_or_404, redirect

from django.http import HttpResponse

from django.core.paginator import Paginator, EmptyPage, PageNotAnInteger

from ask.forms import RegisterForm, LoginForm, MakeQuestionForm, SettingsForm, CreateAnswerForm
from models import *


# from django.views.decorators.cache import cache_page

# @cache_page(600 * 15)
def paginate(objects_list, request):
    paginator = Paginator(objects_list, 5)

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
    qs, paginator = paginate(questions, request)
    likes = []
    if request.user.is_authenticated:
        p = Profile.objects.by_user(request.user)
        for i in qs:
            like = Like.objects.byProfileQuestion(p, i)
            if like:
                likes.append(like.value)
            else:
                likes.append(0)
    return render(request, 'index.html', {
        'questions': qs,
        'atags': Tag.objects.all(),
        'likes': likes
    })


def bytag(request, tag):
    questions = Question.objects.by_tag(tag)
    objects_page, paginator = paginate(questions, request)
    return render(request, 'bytag.html', {
        "questions": objects_page,
        'tag': tag,
        'atags': Tag.objects.all()
    })


def hot(request):
    questions = Question.objects.top()
    objects_page, paginator = paginate(questions, request)
    return render(request, 'hot.html', {
        "questions": objects_page,
    })


def ask(request):
    if not request.user.is_authenticated:
        return HttpResponseRedirect('/login')

    if request.POST:
        form = MakeQuestionForm(request.POST, request.FILES)
        if form.is_valid():
            idd = form.save(request)
            return HttpResponseRedirect('/question/' + str(idd))
    else:
        form = MakeQuestionForm()

    return render(request, 'makequestion.html', {
        'form': form,
    })


def login_to_system(request):
    if request.user.is_authenticated:
        return HttpResponseRedirect('/')
    contin = request.GET.get('continue', '/')

    errors = False
    if (request.method == "POST"):
        form = LoginForm(request.POST)
        login_name = request.POST['login']
        password = request.POST['password']
        if not login_name or not password:
            errors = True
        if not errors:
            user = authenticate(username=login_name, password=password)
            if user:
                login(request, user)
                return redirect(contin)
            else:
                errors = True
    else:
        form = LoginForm()

    return render(request, 'login.html', {
        'form': form,
        'errors': errors,
        'continue': contin,
    })


def signup(request):
    if request.user.is_authenticated:
        return HttpResponseRedirect('/')

    if request.POST:
        form = RegisterForm(request.POST, request.FILES)
        if form.is_valid():
            form.create_account()
            return HttpResponseRedirect('/login')
    else:
        form = RegisterForm()

    return render(request, 'register.html', {
        'form': form,
    })


def settings(request):
    if not request.user.is_authenticated:
        return HttpResponseRedirect('/login')

    if request.POST:
        form = SettingsForm(request.POST, request.FILES, user=request.user)
        if form.is_valid():
            form.update_account()
            return HttpResponseRedirect('/')
    else:
        form = SettingsForm(user=request.user,
                            initial={'email': request.user.email,
                                     'name': request.user.username,
                                     'image': Profile.objects.by_user(request.user).avatar})

    return render(request, 'settings.html', {
        'form': form,
    })


def logout_user(request):
    if not request.user.is_authenticated:
        return HttpResponseRedirect('/')
    logout(request)
    return HttpResponseRedirect('/')


def like_question(request):
    if not request.method == 'GET':
        return JsonResponse({'error': '6'})
    try:
        question_id = request.GET['id']
    except:
        return JsonResponse({'error': '7'})
    if not request.user.is_authenticated:
        return JsonResponse({'error': '1'})
    if not question_id:
        return JsonResponse({'error': '5'})
    try:
        q = Question.objects.get(id=question_id)
    except:
        return JsonResponse({'error': '2'})
    # if q.author == Profile.objects.by_user(request.user):
    #     return JsonResponse({'error': '3'})
    like = Like.objects.get_or_create(profile=Profile.objects.by_user(request.user), question=q)[0]
    like.save()
    if like.value == 1:
        return JsonResponse({'error': '4', 'rating': q.rating, 'myrate': like.value})
    like.value += 1
    q.rating += 1
    like.save()
    q.save()
    return JsonResponse({'error': '0', 'rating': q.rating, 'myrate': like.value})


def dislike_question(request):
    if not request.method == 'GET':
        return JsonResponse({'error': '6'})
    try:
        question_id = request.GET['id']
    except:
        return JsonResponse({'error': '7'})
    if not request.user.is_authenticated:
        return JsonResponse({'error': '1'})
    if not question_id:
        return JsonResponse({'error': '5'})
    try:
        q = Question.objects.get(id=question_id)
    except:
        return JsonResponse({'error': '2'})
    # if q.author == Profile.objects.by_user(request.user):
    #     return JsonResponse({'error': '3'})
    like = Like.objects.get_or_create(profile=Profile.objects.by_user(request.user), question=q)[0]
    like.save()
    if like.value == -1:
        return JsonResponse({'error': '4', 'rating': q.rating, 'myrate': like.value})
    like.value -= 1
    q.rating -= 1
    like.save()
    q.save()
    return JsonResponse({'error': '0', 'rating': q.rating, 'myrate': like.value})


def dislike_answer(request):
    if not request.method == 'GET':
        return JsonResponse({'error': '6'})
    try:
        answer_id = request.GET['id']
    except:
        return JsonResponse({'error': '7'})
    if not request.user.is_authenticated:
        return JsonResponse({'error': '1'})
    if not answer_id:
        return JsonResponse({'error': '5'})
    try:
        a = Answer.objects.get(id=answer_id)
    except:
        return JsonResponse({'error': '2'})
    # if q.author == Profile.objects.by_user(request.user):
    #     return JsonResponse({'error': '3'})
    like = AnswerLike.objects.get_or_create(profile=Profile.objects.by_user(request.user), answer=a)[0]
    like.save()
    if like.value == -1:
        return JsonResponse({'error': '4', 'rating': a.rating, 'myrate': like.value})
    like.value -= 1
    a.rating -= 1
    like.save()
    a.save()
    return JsonResponse({'error': '0', 'rating': a.rating, 'myrate': like.value})


def like_answer(request):
    if not request.method == 'GET':
        return JsonResponse({'error': '6'})
    try:
        answer_id = request.GET['id']
    except:
        return JsonResponse({'error': '7'})
    if not request.user.is_authenticated:
        return JsonResponse({'error': '1'})
    if not answer_id:
        return JsonResponse({'error': '5'})
    try:
        a = Answer.objects.get(id=answer_id)
    except:
        return JsonResponse({'error': '2'})
    # if q.author == Profile.objects.by_user(request.user):
    #     return JsonResponse({'error': '3'})
    like = AnswerLike.objects.get_or_create(profile=Profile.objects.by_user(request.user), answer=a)[0]
    like.save()
    if like.value == 1:
        return JsonResponse({'error': '4', 'rating': a.rating, 'myrate': like.value})
    like.value += 1
    a.rating += 1
    like.save()
    a.save()
    return JsonResponse({'error': '0', 'rating': a.rating, 'myrate': like.value})


def question(request, question_id):
    q = get_object_or_404(Question, id=question_id)
    answers, paginator = paginate(Answer.objects.filter_question(q), request)

    if request.POST:
        form = CreateAnswerForm(request.POST, request.FILES, user=request.user, question=q)
        if form.is_valid() and request.user.is_authenticated:
            form.create_question()
            return HttpResponseRedirect('/question/' + str(question_id))
    else:
        form = CreateAnswerForm(user=request.user, question=q)
    # form = AnswerForm(initial={'question': str(pk)})
    return render(request, 'question.html', {
        'question': q,
        'answers': answers,
        'form': form,
        'atags': Tag.objects.all()
    })
