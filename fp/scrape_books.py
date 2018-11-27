from bs4 import BeautifulSoup as bs
from urllib.request import urlopen

url = 'https://thegreatestbooks.org/lists/159'
soup = bs(urlopen(url))

for a in soup.findAll("a", href=True):
    if '/items/' in a['href']:
        index_last_by = a.text.rfind('by')
        book_title = a.text[0:index_last_by - 1]

        with open('books.txt', 'a') as f:
            f.write(book_title)
            f.write('\n')
