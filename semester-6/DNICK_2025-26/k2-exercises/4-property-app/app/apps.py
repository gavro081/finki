from django.apps import AppConfig as AppConf


class AppConfig(AppConf):
    name = 'app'

    def ready(self):
        from . import signals