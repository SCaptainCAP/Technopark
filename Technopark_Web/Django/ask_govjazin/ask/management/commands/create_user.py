from django.contrib.auth.models import User
from django.core.management.base import BaseCommand

from ask.models import Profile, Question


class Command(BaseCommand):
    help = "Create user"

    def add_arguments(self, parser):
        parser.add_argument('uname')
        parser.add_argument('uemail')
        parser.add_argument('upass')

    def handle(self, *args, **options):
        u = User.objects.create_user(options['uname'], options['uemail'], options['upass'])
        u.save()
        p = Profile(user = u)
        p.save()