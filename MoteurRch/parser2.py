#!/usr/bin/python3
# -*-coding:Utf-8 -*


 
from html.parser import HTMLParser


import requests
from bs4 import BeautifulSoup

from collections import Counter
import pickle


dejaParser = [];


listtmp = []

for i in range(1,2):
	fichier = open("/tmp/fic"+str(i)+".html")

urls = ["http://www.lemonde.fr", "http://www.google.fr", "http://www.bing.com", "http://www.lefigaro.com"]

def setUrl(fichier):
	try:
		urlListRead = open("./url-list.txt", "r")
		urlList = urlListRead.read()
		urlList = urlList.split("\n")
		if (fichier in urlList):
			print("URL IN LIST")
		else :
			urlListWrite = open("./url-list.txt", "a")
			urlListWrite.write(fichier + "\n")
	except:
		return -1
	return 0	

def getLinks(fichier):
	try:
		soup = BeautifulSoup(fichier,"lxml")
		soup.prettify()
		listOfUrl = soup.find_all("a", href = True)
		for link in listOfUrl:
			if (link["href"].startswith("http") or link["href"].startswith("ftp") or link["href"].startswith("file") or link["href"].startswith("/")):
				setUrl(link["href"])
	except:
		return -1
	return 0

#getLinks(fichier)



def getContenu(fichier):
	print("parse le contenu du lien....")
	tab_liens = []
	soup = BeautifulSoup(fichier,"lxml")
	titre = soup.title.string
	print(titre)
	for m in soup.find_all('html'):#on enlevera le for apres
		for s in soup.find_all(['script', 'style']):
			s.decompose()
		contenu = m.get_text().lower()
		lignes = (l.strip() for l in contenu.splitlines())
		jointure = (p.strip() for l in lignes for p in l.split(" "))
		contenu = '\n'.join(j for j in jointure if j)
		tab_liens.append(contenu.split("\n"))
	dict_mots = {}
	dict_mots = Counter(contenu.split("\n"))
	fic = open("./contenu.txt", "w")
	for cle , valeur in dict_mots.items():
		tmp = "{} {}\n".format(cle,valeur)
		fic.write(tmp)
		fic.flush()
	fic.close()
	print('OKKKKKKKK')
	#print(dict_mots)
	return contenu
getContenu(fichier)










