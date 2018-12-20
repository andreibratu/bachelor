from controller import HomeworkController
from repo import HomeworkRepository
from homework import Homework


repo = HomeworkRepository()
controller = HomeworkController(hw_repo=repo)


def test_all():
    # Check if it loads properly
    assert len(controller.all()) == 5


def test_insertion():
    old_len = len(repo.homework)
    controller.insert(name='Foo', hw='bar')
    assert len(repo.homework) == old_len + 1


def test_dishonesty():
    repo.homework = {}
    repo.homework = {
        '1': Homework(name='John', hw='Foo bar baz qw rty yui'),
        '2': Homework(name='Mary', hw='bar zx cv bn'),
        '3': Homework(name='Queen', hw='a b c t s f g h i e r y z o z l'),
        '4': Homework(name='King', hw='b c t')
    }
    assert len(controller.check_dishonest()) == 2
    assert '25' in controller.check_dishonest()[0]
    assert '100' in controller.check_dishonest()[1]


def run_tests():
    test_all()
    test_insertion()
    test_dishonesty()
