from django.db import models
from django.contrib.auth.models import User
from django.utils import timezone

from ask_govjazin.settings import BASE_DIR


class ProfileManager(models.Manager):
    def by_user(self, u):
        return self.all().filter(user=u)[0]


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
    data = models.CharField(max_length=420)

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

    def getAnswerCount(self):
        return Answer.objects.filter_question(self).count()

    def getLikes(self):
        return Like.objects.filter(question=self)

    def getUserLike(self, user):
        l = Like.objects.filter(question=self, profile=Profile.objects.by_user(user))
        if l:
            return l[0]
        else:
            return None

    def __unicode__(self):
        return self.title


class AnswerManager(models.Manager):
    def filter_question(self, q):
        return self.all().filter(question=q).order_by('rating', 'creation_time')


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


class LikeManager(models.Manager):
    def byQuestion(self, q):
        self.all().filter(question=q)

    def byProfile(self, p):
        self.all().filter(profile=p)

    def byProfileQuestion(self, p, q):
        self.all().filter(profile=p, question=q)


class Like(models.Model):
    value = models.IntegerField(default=0)
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
    objects = LikeManager()

    class Meta:
        unique_together = (("profile", "question"),)

    def __unicode__(self):
        return unicode(self.value)


class AnswerLikeManager(models.Manager):
    pass


class AnswerLike(models.Model):
    value = models.IntegerField(default=0)
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
    objects = AnswerLikeManager

    class Meta:
        unique_together = (("profile", "answer"),)

    def __unicode__(self):
        return unicode(self.value)
