from django.contrib.auth.models import User
from django.core.management.base import BaseCommand

from ask.models import Profile, Question, Tag
from ask_govjazin.settings import BASE_DIR


class Command(BaseCommand):
    def handle(self, *args, **options):
        qs = Question.objects.all().order_by('-rating')
        users=[]
        for i in range(len(qs)):
            if not qs[i].author in users:
                users.append(qs[i].author)
        f = open(BASE_DIR + '/static/updatable_data/bestusers.txt', 'w')
        try:
            for i in range(min(20, len(users))):
                f.write(users[i].user.username + '\n')
        finally:
            f.close()
