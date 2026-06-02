import datetime

import django.utils.timezone
from django.contrib import admin

# Register your models here.
from .models import *
# Агенти и Карактеристики може да бидат додадени само од супер-корисници
# Агентите, Карактеристиките и Недвижностите се прикажани со нивното име (презиме, површина и опис ако ги имаат, соодветно)
# Огласи за продажба може да бидат додадени само од агенти и по автоматизам агентот кој додава оглас е еден од задолжените за продажба на таа недвижност
# Еден оглас може да биде избришан само ако нема додадено ниту една карактеристика која го опишува
# Огласите можат да бидат менувани само од агенти кои се задолжени за продажба на тој оглас, а останатите агенги може само да ги гледаат тие огласи
# На супер-корисниците во Админ панелот им се прикажуваат само огласите кои се објавени на денешен датум

class AgentInline(admin.TabularInline):
    model = AgentProperties
    extra = 0

class CharacteristicInline(admin.TabularInline):
    model = PropertyCharacteristics
    extra = 0

class PropertyAdmin(admin.ModelAdmin):
    inlines = [AgentInline, CharacteristicInline]

    def has_add_permission(self, request):
        if not Agent.objects.all().exists():
            return True
        return Agent.objects.filter(user=request.user).exists()

    def save_model(self, request, obj: Property, form, change):
        agent = Agent.objects.filter(user=request.user).first()
        super().save_model(request, obj, form, change)
        if not change and agent is not None:
            AgentProperties.objects.create(agent=agent, property=obj)

    def has_delete_permission(self, request, obj=None):
        return not PropertyCharacteristics.objects.filter(property=obj).exists()

    def has_change_permission(self, request, obj = None):
        if request.user.is_superuser:
            return True
        if obj is None:
            return AgentProperties.objects.filter(agent__user=request.user).exists()
        return AgentProperties.objects.filter(agent__user=request.user, property=obj).exists()

    def has_view_permission(self, request, obj = None):
        return request.user.is_authenticated

    def get_queryset(self, request):
        qs = Property.objects.all()
        if request.user.is_superuser:
            qs = qs.filter(publish_date=datetime.date.today())

        return qs

class AgentAdmin(admin.ModelAdmin):
    def has_add_permission(self, request):
        return request.user.is_superuser

class CharacteristicAdmin(admin.ModelAdmin):

    def has_add_permission(self, request):
        return request.user.is_superuser


admin.site.register(Agent, AgentAdmin)
admin.site.register(Property, PropertyAdmin)
admin.site.register(Characteristic, CharacteristicAdmin)