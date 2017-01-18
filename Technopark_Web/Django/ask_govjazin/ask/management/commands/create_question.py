from django.contrib.auth.models import User
from django.core.management.base import BaseCommand

from ask.models import Profile, Question, Tag


class Command(BaseCommand):
    help = "Create question"

    def add_arguments(self, parser):
        parser.add_argument(dest='count', type=int)
        parser.add_argument(dest='title')
        parser.add_argument(dest='text')
        parser.add_argument(dest='author')
        parser.add_argument(dest='tag', nargs = 3)

    def handle(self, *args, **options):
        for i in range(options['count']):
            p = Profile.objects.by_user(User.objects.get_by_natural_key(options['author']))[0]
            tags = options['tag']
            tags_objs = []
            for tag in tags:
                tag_obj = Tag.objects.get_or_create(data=(tag + str(i)))[0]
                tag_obj.save()
                tags_objs.append(tag_obj)

            q = Question(title = options['title'] + str(i),
                         text = options['text'] + str(i),
                         author = p)
            q.save()

            for tag_obj in tags_objs:
                q.tags.add(tag_obj)

            q.save()