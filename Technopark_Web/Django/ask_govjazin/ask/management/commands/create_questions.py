import random
import string
from sqlite3 import IntegrityError

from django.contrib.auth.models import User
from django.core.management.base import BaseCommand
from django.db import transaction

from ask.models import Profile, Question, Tag


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
                    random_idx = random.randint(0, Profile.objects.count() - 1)
                    random_profile = Profile.objects.all()[random_idx]
                    tags=[]
                    for j in range(3):
                        tag_obj = Tag.objects.get_or_create(data=id_generator())[0]
                        tag_obj.save()
                        tags.append(tag_obj)
                    q = Question(title=id_generator(),
                                 text=id_generator(100),
                                 author=random_profile,)
                    q.save()
                    q.tags = tags
                    q.save()
        except IntegrityError:
            pass