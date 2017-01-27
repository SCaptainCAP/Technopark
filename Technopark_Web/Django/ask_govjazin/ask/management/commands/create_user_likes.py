import random
import string
from sqlite3 import IntegrityError

from django.contrib.auth.models import User
from django.core.management.base import BaseCommand
from django.db import transaction

from ask.models import Profile, Question, Tag, Like


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
                    random_idx = random.randint(0, Question.objects.count() - 1)
                    random_question = Question.objects.all()[random_idx]
                    random_idp = random.randint(0, Profile.objects.count() - 1)
                    random_p = Profile.objects.all()[random_idp]
                    l = Like.objects.get_or_create(profile=random_p, question=random_question)[0]
                    l.save()
                    r = random.randint(-1, 1)
                    l.value = r
                    random_question.rating += r
                    random_question.save()
                    l.save()
        except IntegrityError:
            pass