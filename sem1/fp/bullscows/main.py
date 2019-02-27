from repo import Repository
from service import Service
from ui import UI

repo = Repository()
service = Service(repo)
ui = UI(service)

ui.loop()
