#!/usr/bin/python3
# -*-coding:Utf-8 -*


 
from html.parser import HTMLParser

mots = []
liens = []
import requests
from bs4 import BeautifulSoup
 
req = requests.get('http://www.lemonde.fr')
page = req.content
soup = BeautifulSoup(page)
#print (soup.prettify())

titre = soup.title.string
print(titre)


#renvoie les balises h1
def getLiens(fichier, url):
	print("parse dans les liens")
	try:
		soup = BeautifulSoup(open("/tmp/"+fichier, "html.parser"))
		soup.prettify()
		tab_liens = []
		for a in soup.find_all('a', href = True):
			lien = a["href"]
			if(lien.startswith("http", "https", "ftp") and (lien != url) and not(lien.startswith("GIF","png","img","jpeg"))):
				if(lien not in tab_liens):
					liens.append(a["href"])
		print(len(tab_liens))
		print(tab_liens)
		return tab_liens
	except:
		return []
#getLiens(liens)

def getContenu(fichier):
	print("parse le contenu du lien....")
	tab_liens = []
	#soup = BeautifulSoup(open("/tmp/"+fichier), "html.parser")
	for m in soup.find_all('html'):#on enlevera le for apres
		for s in soup.find_all(['script', 'style']):
			s.decompose()
		contenu = m.get_text().lower()
		lignes = (l.strip() for l in contenu.splitlines())
		#jointure = (p.strip() for l in lignes for p in l.split(" "))
		contenu = '\n'.join(j for j in lignes if j)
		#contenu2 = unicodedata.normailze('NFKD', contenu).encode('ascii', 'ignore')
		print(contenu)
		return contenu
getContenu(mots)


def getMots(fichier):
	print("parse les mots lien....")
	tab_liens = []
	#soup = BeautifulSoup(open("/tmp/"+fichier), "html.parser")
	for m in soup.find_all('a'):#on enlevera le for apres
		
		mot = m.get_text().lower()
		lignes = (l.strip() for l in mot.splitlines())
		jointure = (p.strip() for l in lignes for p in l.split(" "))
		mot = '\n'.join(j for j in jointure if j)
		#mot2 = unicodedata.normailze('NFKD', mot).encode('ascii', 'ignore')
		print(mot)
	return mot
getMots(mots)







