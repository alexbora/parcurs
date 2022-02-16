#!/usr/bin/env python3
import locale
import calendar
import datetime
import random
from calendar import month_name
import yagmail
import functools
locale.setlocale(locale.LC_ALL, '')
import subprocess


def mail():
    subprocess.call("/Users/alex/dev/PARCURS/foaie_2")
    # subprocess.call("/mnt/t400.linux/home/alex/Documente/parcurs/foaie_2")    
    sender_email = "t400.linux@gmail.com"
    receiver_email = "t400.linux@gmail.com", 'alexandru.bora@renault-trucks.com'
    subject = "foaie_parcurs - B-151-VGT - Alex Bora" 
    yag = yagmail.SMTP(user=sender_email, password="Cragger2011")
    # contents = ["/mnt/t400.linux/home/alex/Documente/parcurs/foaie.xlsx"]
    contents = ["/Users/alex/dev/PARCURS/foaie.xlsx"]

    yag.send(receiver_email, subject, contents)

mail()
