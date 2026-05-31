from django.contrib import admin
from .models import *
from datetime import date

# Register your models here.
class ArtistAdmin(admin.ModelAdmin):
    def has_add_permission(self, request):
        return request.user.is_superuser

class ExhibitionAdmin(admin.ModelAdmin):
    def has_add_permission(self, request):
        return request.user.is_superuser

    def get_queryset(self, request):
        qs = super().get_queryset(request)

        if request.user.is_superuser:
            qs = qs.filter(end_date__gt=date.today())

        artist = Artist.objects.filter(user=request.user).first()
        if artist:
            qs = qs.filter(artwork__artist=artist)

        return qs

class ArtworkAdmin(admin.ModelAdmin):
    def has_add_permission(self, request):
        return Artist.objects.filter(user=request.user).exists()

    def has_change_permission(self, request, obj: Artwork = None):
        if obj is None:
            return Artist.objects.filter(user=request.user).exists()
        return request.user == obj.artist.user

    def save_model(self, request, obj, form, change):
        if not change:
            obj.artist = Artist.objects.get(user=request.user)
        super().save_model(request, obj, form, change)


admin.site.register(Artist, ArtistAdmin)
admin.site.register(Exhibition, ExhibitionAdmin)
admin.site.register(Artwork, ArtworkAdmin)