from services.Engine import Engine


class Test():
    def add_attempt_with_random_id(self):
        engine = Engine.get_instance()

        network_service = engine.network_service
