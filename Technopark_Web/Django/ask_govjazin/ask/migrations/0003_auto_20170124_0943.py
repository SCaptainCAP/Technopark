# -*- coding: utf-8 -*-
# Generated by Django 1.10.5 on 2017-01-24 09:43
from __future__ import unicode_literals

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('ask', '0002_auto_20161210_1216'),
    ]

    operations = [
        migrations.AlterField(
            model_name='profile',
            name='avatar',
            field=models.ImageField(default=b'static/img/no-avatar.png', upload_to=b'uploads/images/avatars_%Y-%m-%d'),
        ),
    ]
