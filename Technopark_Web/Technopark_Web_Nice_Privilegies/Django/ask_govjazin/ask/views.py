from django.shortcuts import render

from django.http import HttpResponse

from django.views.decorators.cache import cache_page

@cache_page(600 * 15)
def hello(request):
    gett = ''
    for key, value in request.GET.iteritems():
        gett = key + '=' + value + ', '
#    postt = ''
#    for (key, value in request.POST.iteritems()):
#        postt = key + '=' + value + ', '
    a = 'Request method: ' + request.method + '<br />GET params: ' + gett + '<br />'#POST params: ' + '<br />'# + postt + '\n'
    return HttpResponse(a)
	#return render(request, "ask/index.html")
