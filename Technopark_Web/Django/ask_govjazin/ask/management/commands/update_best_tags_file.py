from django.contrib.auth.models import User
from django.core.management.base import BaseCommand

from ask.models import Profile, Question, Tag
from ask_govjazin.settings import BASE_DIR


class Command(BaseCommand):
    def handle(self, *args, **options):
        tags = []
        for tag in Tag.objects.all():
            tags.append({'tag': tag.data, 'count': len(Question.objects.by_tag(tag))})
        tags = sorted(tags, reverse=True)
        f = open(BASE_DIR + '/static/updatable_data/besttags.txt', 'w')
        try:
            for i in range(min(20, len(tags))):
                f.write(tags[i].get('tag') + '\n')
        finally:
            f.close()
