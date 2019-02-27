class UI:


    def __init__(self, service):
        self.service = service


    def loop(self):
        name = input('What is your name: ')
        print('Welcome to bulls and cows!')
        print("Input 'play' to start, 'exit' to leave or 'scores' for scores")
        while True:

            cmd = input('> ')

            if cmd == 'play':
                tries = 15
                flag = False
                self.service.pick_word()

                while tries != 0:
                    print(self.service.answer)
                    w = input('Give me a word: ')

                    ans, b, c = self.service.query(w)

                    if ans:
                        print("You've won with a score of {}!".format(tries))
                        self.service.add_score(name, tries)
                        flag = True
                        break

                    else:
                        if b is None and c is None:
                            print('Invalid word!')

                        else:
                            print('You got {} bulls and {} cows'.format(b, c))
                        tries -= 1
                        print('You have {} tries left..'.format(tries))

                if not flag:
                    print("You've lost!")

                continue

            elif cmd == 'scores':
                self.service.print_scores()

            elif cmd == 'exit':
                # exit
                print('Goodbye')
                break

            else:
                print('Invalid cmd')
                break
