from __future__ import unicode_literals

from django.db import models
from django.contrib.auth.models import User
 
class Door(models.Model):
	name = models.CharField(max_length=255)
	open = models.BooleanField(default=True)
	controllable = models.BooleanField(default=False)

	def __str__(self):
		if self.name=='':
			return 'd.%s' % (self.id)
		else:
			return '%s (d.%s)' % (self.name, self.id)

class Card(models.Model):
	id = models.IntegerField(primary_key=True)
	owner = models.ForeignKey(User, blank=True, null=True)
	doors = models.ManyToManyField(Door, blank=True)

	def __str__(self):
		if self.owner==None:
			return '*no owner* (%s)' % (self.id)
		else: 
			return '%s %s (%s)' % (
				self.owner.first_name, self.owner.last_name, self.id,
				)

class Log(models.Model):
	datetime = models.DateTimeField(auto_now_add=True)
	door = models.ForeignKey(Door)
	card = models.ForeignKey(Card, blank=True, null=True)
	legal_access = models.BooleanField(default=False)

	def __str__(self):
		return '%s | %s : %s' % (
			self.id, self.door, self.card
			)