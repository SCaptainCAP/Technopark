from django.db import models
from django.contrib.auth.models import User
from django.utils import timezone


class Profile(models.Model):
    avatar = models.ImageField(upload_to = '/uploads/images/%Y-%m-%d',
                               default= '/static/images/sample.jpg'
                               )
    rating = models.IntegerField(default = 0)
    user = models.OneToOneField(
        User,
        on_delete = models.CASCADE,
        primary_key = True,
    )

    def __unicode__(self):
        return self.user.username


class Tag(models.Model):
    data = models.CharField(max_length = 42)

    def __unicode__(self):
        return self.data


class QuestionManager(models.Manager):
    pass
    # def get_query_set(self):
    #     return super(QuestionManager, self).get_query_set()


class Question(models.Model):
    title = models.CharField(max_length = 255)
    text = models.TextField()
    tags = models.ManyToManyField(Tag)
    rating = models.IntegerField(default = 0)
    author = models.ForeignKey(
        Profile,
        on_delete = models.CASCADE,
        null = True,
    )
    creation_time = models.DateTimeField(default = timezone.now)

    questionManager = QuestionManager()

    def __unicode__(self):
        return self.title


class Answer(models.Model):
    is_correct = models.BooleanField(default=False)
    text = models.TextField()
    rating = models.IntegerField(default = 0)
    author = models.ForeignKey(
        Profile,
        on_delete = models.CASCADE,
        null = True,
    )
    creation_time = models.DateTimeField(default = timezone.now)
    question = models.ForeignKey(
        Question,
        on_delete = models.CASCADE
    )

    def __unicode__(self):
        return self.text


class Like(models.Model):
    value = models.IntegerField()
    profile = models.ForeignKey(
        Profile,
        on_delete = models.CASCADE,
        null = True,
    )
    question = models.ForeignKey(
        Question,
        on_delete = models.CASCADE,
        null = True,
    )

    class Meta:
        unique_together = (("profile", "question"),)

    def __unicode__(self):
        return unicode(self.value)


class AnswerLike(models.Model):
    value = models.IntegerField()
    profile = models.ForeignKey(
        Profile,
        on_delete = models.CASCADE,
        null = True,
    )
    answer = models.ForeignKey(
        Answer,
        on_delete = models.CASCADE,
        null = True,
    )

    class Meta:
        unique_together = (("profile", "answer"),)

    def __unicode__(self):
        return unicode(self.value)