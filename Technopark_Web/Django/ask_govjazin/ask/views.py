from django.shortcuts import render

from django.http import HttpResponse

from django.views.decorators.cache import cache_page

@cache_page(600 * 15)
def basewsgi(request):
	gett = ''
	for key, value in request.GET.iteritems():
		gett = key + '=' + value + '<br>'+gett
	postt = ''
	for key in request.POST:
		postt= key+ '='+ request.POST[key]+'<br>'+postt
	a = 'Request method: ' + request.method + '<br />GET params:<br> ' + gett + '<br /> POST params: ' + '<br />' + postt + '\n'
	return HttpResponse(a)
	
def index(request):
	return render(request, 'index.html')
	
#def index(request):
#	return render(request, 'index.html')
