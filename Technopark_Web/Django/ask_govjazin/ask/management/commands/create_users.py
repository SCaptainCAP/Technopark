import random
import string
from sqlite3 import IntegrityError

from django.contrib.auth.models import User
from django.core.management.base import BaseCommand
from django.db import transaction

from ask.models import Profile, Question


def id_generator(size=6, chars=string.ascii_uppercase + string.digits):
    return ''.join(random.choice(chars) for _ in range(size))


class Command(BaseCommand):
    help = "Create [count] random accounts"

    def add_arguments(self, parser):
        parser.add_argument('count')

    def handle(self, *args, **options):
        try:
            with transaction.atomic():
                for i in range(int(options['count'])):
                    u = User.objects.create_user(username=id_generator() + str(i),
                                                 email=id_generator() + str(i) + '@gmail.com',
                                                 password=id_generator())
                    u.save()
                    p = Profile(user=u)
                    p.save()
        except IntegrityError:
            pass
