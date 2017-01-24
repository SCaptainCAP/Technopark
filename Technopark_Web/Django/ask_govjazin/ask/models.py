from django.db import models
from django.contrib.auth.models import User
from django.utils import timezone

from ask_govjazin.settings import BASE_DIR


class ProfileManager(models.Manager):
    def by_user(self, u):
        return self.all().filter(user=u)


class Profile(models.Model):
    avatar = models.ImageField(
        upload_to='uploads',
        default='static/img/no-avatar.png'
    )
    rating = models.IntegerField(default=0)
    user = models.OneToOneField(
        User,
        on_delete=models.CASCADE,
        primary_key=True,
    )
    objects = ProfileManager()

    def __unicode__(self):
        return self.user.username


class TagsManager(models.Manager):
    pass

class Tag(models.Model):
    data = models.CharField(max_length=42)

    objects = TagsManager()
    def __unicode__(self):
        return self.data


class QuestionManager(models.Manager):
    def top(self):
        return self.all().order_by('-rating')

    def new(self):
        return self.all().order_by('creation_time')

    def by_tag(self, tag):
        return self.all().filter(tags__data=tag)


class Question(models.Model):
    title = models.CharField(max_length=255)
    text = models.TextField()
    tags = models.ManyToManyField(Tag)
    rating = models.IntegerField(default=0)
    author = models.ForeignKey(
        Profile,
        on_delete=models.CASCADE,
        null=True,
    )
    creation_time = models.DateTimeField(default=timezone.now)

    objects = QuestionManager()

    def __unicode__(self):
        return self.title


class AnswerManager(models.Manager):
    def filter_question(self, q):
        return self.all().filter(question=q)


class Answer(models.Model):
    is_correct = models.BooleanField(default=False)
    text = models.TextField()
    rating = models.IntegerField(default=0)
    author = models.ForeignKey(
        Profile,
        on_delete=models.CASCADE,
        null=True,
    )
    creation_time = models.DateTimeField(default=timezone.now)
    question = models.ForeignKey(
        Question,
        on_delete=models.CASCADE
    )
    objects = AnswerManager()

    def __unicode__(self):
        return self.text


class Like(models.Model):
    value = models.IntegerField()
    profile = models.ForeignKey(
        Profile,
        on_delete=models.CASCADE,
        null=True,
    )
    question = models.ForeignKey(
        Question,
        on_delete=models.CASCADE,
        null=True,
    )

    class Meta:
        unique_together = (("profile", "question"),)

    def __unicode__(self):
        return unicode(self.value)


class AnswerLike(models.Model):
    value = models.IntegerField()
    profile = models.ForeignKey(
        Profile,
        on_delete=models.CASCADE,
        null=True,
    )
    answer = models.ForeignKey(
        Answer,
        on_delete=models.CASCADE,
        null=True,
    )

    class Meta:
        unique_together = (("profile", "answer"),)

    def __unicode__(self):
        return unicode(self.value)
