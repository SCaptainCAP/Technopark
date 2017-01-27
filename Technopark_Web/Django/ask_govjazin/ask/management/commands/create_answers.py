import random
import string
from sqlite3 import IntegrityError

from django.contrib.auth.models import User
from django.core.management.base import BaseCommand
from django.db import transaction

from ask.models import Profile, Question, Tag, Answer


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
                    a = Answer(text=id_generator(200), author=random_p, question=random_question)
                    a.save()
        except IntegrityError:
            pass