from ui import CommandUI, MenuUI
import test

print('FP3-4 project, a complex numbers list manager!')

while True:
    try:
        menu = int(input('Type 0 for the cool CLI or 1 for boring menu: '))
        if menu == 0:
            ui = CommandUI()
            ui.loop()
            break
        if menu == 1:
            ui = MenuUI()
            ui.loop()
            break
        continue

    except EOFError:
        print('\nHave a lovely day!')
        break
