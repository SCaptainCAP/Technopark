# -*- coding: utf-8 -*-
# Generated by Django 1.10.5 on 2017-01-24 12:47
from __future__ import unicode_literals

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('ask', '0006_auto_20170124_1233'),
    ]

    operations = [
        migrations.AlterField(
            model_name='profile',
            name='avatar',
            field=models.ImageField(default=b'static/img/no-avatar.png', upload_to=b'uploads'),
        ),
    ]
