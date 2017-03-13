from django.conf.urls import url
from django.contrib.auth.views import login, logout
from . import views

urlpatterns = [
	url(r'^$', views.index, name='index'),
	url(r'^cards$', views.cards, name='cards'),
	url(r'^log$', views.log, name='log'),
	url(r'^users$', views.users, name='users'),


	url(r'^login$', login, {'template_name': 'admin/login.html'}, name='login'),
	url(r'^logout$', logout, {'next_page': '/'}, name='logout'),
	url(r'^open_door$', views.open_door, name='open_door'),
	url(r'^edit_card$', views.edit_card, name='edit_card'),
]