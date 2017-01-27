from django import template

from ask.models import Like, Profile, AnswerLike

register = template.Library()


@register.assignment_tag
def getUserLike(q, u):
    l = Like.objects.filter(question=q, profile=Profile.objects.by_user(u))
    if l:
        return l[0].value
    else:
        return 0

@register.assignment_tag
def getUserLikeAnswer(a, u):
    l = AnswerLike.objects.filter(answer=a, profile=Profile.objects.by_user(u))
    if l:
        return l[0].value
    else:
        return 0