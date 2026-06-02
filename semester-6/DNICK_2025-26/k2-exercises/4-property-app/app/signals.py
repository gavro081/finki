from django.db.models.signals import pre_save, pre_delete
from django.dispatch import receiver
from django.utils.timezone import now
from .models import *

# Кога еден оглас/недвижнина ќе се означи како продадена, потребно е сите агенти поврзани со неа да ја инкрементираат својата продажба

@receiver(pre_save, sender=Property)
def agents_increment_counter(sender, instance: Property, **kwargs):
    if not instance.is_sold:
        return

    if instance.pk:
        old = Property.objects.filter(pk=instance.pk).first()
        if old is not None and old.is_sold:
            return

    agents = AgentProperties.objects.filter(property=instance)
    for a in agents:
        agent = a.agent
        agent.num_sales = agent.num_sales + 1
        agent.save()