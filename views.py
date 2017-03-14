from django.shortcuts import render
from django.http import HttpResponse, HttpResponseServerError, HttpResponseRedirect
from django.contrib.auth.models import User
from .models import Door, Card, Log
from .forms import CardForm, OpenDoorForm

def index(request):
	data = {
		'doors': Door.objects.all(),
		'cards': Card.objects.all(),
		'users': User.objects.all(),
		'log': Log.objects.all(),
		'open_door_form': OpenDoorForm(),
		'edit_card_form': CardForm(),
	}

	return render(request, 'WebControl/home.html', {'data': data})

def cards(request):
	data = {
		'doors': Door.objects.all(),
		'cards': Card.objects.all(),
		'users': User.objects.all(),
		'edit_card_form': CardForm(),
	}

	return render(request, 'WebControl/cards.html', {'data': data})

def log(request):
	data = {
		'log': Log.objects.all(),
		'edit_card_form': CardForm(),
	}

	return render(request, 'WebControl/log.html', {'data': data})

def users(request):
	data = {
		'cards': Card.objects.all(),
		'users': User.objects.all(),
	}

	return render(request, 'WebControl/users.html', {'data': data})

def open_door(request):
	if request.method == 'POST':
		door = Door.objects.get(id=request.POST.get('id'))
		form = OpenDoorForm(request.POST, instance=door)
		if form.is_valid():
			open_door = form.save()
			return HttpResponseRedirect('/')

	return HttpResponseRedirect('/')

def edit_card(request):
	if request.method == 'POST':
		form = CardForm(request.POST)
		if form.is_valid():
			edited_card = form.save()
			return HttpResponseRedirect('/')

	return HttpResponseRedirect('/')

def updateDoors(request):
	data = {
		'doors': Door.objects.all(),
		'open_door_form': OpenDoorForm(),
	}
	return render(request, 'WebControl/doors.html', {'data': data})