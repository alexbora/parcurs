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
import glob,  os
from datetime import datetime
from datetime import date
from time import strptime

def name():
    previous_month = date.today().month -1
    previous_year = date.today().year
    month = calendar.month_name[previous_month]
    if previous_month == 0:
        previous_year = previous_year-1

    longdate = datetime.today().strftime('%d.%m.%Y')
    dir = os.getcwd()
    excel =   dir + "/foaie_parcurs_B-151-VGT_" + month.lower() + "_" + str(previous_year) + "_Alex_Bora_" + longdate + ".xlsx"
    exe = dir + "/foaie_2"
    print(excel)
    print(exe)



def mail():
    previous_month = date.today().month -1
    previous_year = date.today().year
    month = calendar.month_name[previous_month]
    if previous_month == 0:
        previous_year = previous_year-1

    longdate = datetime.today().strftime('%d.%m.%Y')
    dir = os.getcwd()
    #excel =   dir + "/foaie_parcurs_B-151-VGT_" + month.lower() + "_" + str(previous_year) + "_Alex_Bora" + ".xlsx"
    #excel = dir + "/foaie_parcurs_B-151-VGT_ianuarie_Alex_Bora_18.02.2022.xlsx"
    excel = "/mnt/t400.linux/home/alex/Documente/parcurs/foaie_parcurs_B-151-VGT_" + month.lower() + "_2022_Alex_Bora.xlsx"
    exe = dir + "/foaie_2"
    excel="/mnt/t400.linux/home/alex/Documente/parcurs/foaie_parcurs_B-151-VGT_martie_2022_Alex_Bora.xlsx"
    #nu citeste corect path, nu a generat nici macar C

    #subprocess.call(exe)
    # subprocess.call("/Users/alex/dev/PARCURS/foaie_2")
    subprocess.call("/mnt/t400.linux/home/alex/Documente/parcurs/foaie_2")    
    sender_email = "t400.linux@gmail.com"
    receiver_email = "t400.linux@gmail.com", 'alexandru.bora@renault-trucks.com'
    subject = "foaie_parcurs_B-151-VGT"+ "_" + month.lower()  + "_" + str(previous_year) + "_Alex Bora" 
    yag = yagmail.SMTP(user=sender_email, password="Cragger2011")
    # contents = ["/mnt/t400.linux/home/alex/Documente/parcurs/foaie.xlsx"]
    # contents = ["/Users/alex/dev/PARCURS/foaie.xlsx"]
    contents = [excel]

    yag.send(receiver_email, subject, contents)

# name()
mail()

