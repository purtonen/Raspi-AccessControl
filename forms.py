from django import forms
from django.utils.translation import ugettext_lazy as _
from django.forms import ModelForm
from django.contrib.auth.models import User
from .models import Card, Door

class CardForm(ModelForm):
	class Meta:
		model = Card
		fields = ['id', 'owner', 'doors']

		widgets = {'id': forms.HiddenInput()}
		help_texts = {
			'doors': _('<br><em>Select doors to open with this card</em>'),
		}

class OpenDoorForm(ModelForm):
	class Meta:
		model = Door
		fields = ['open']
		widgets = {'open': forms.HiddenInput()}