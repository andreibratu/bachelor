from simple_list import SimpleList
from digests import str_digest, float_digest


class HashSet:
    def __init__(self, bucket_count: int = 37):
        self.bucket_count = bucket_count
        self.buckets = [SimpleList() for _ in range(bucket_count)]

    def add(self, key):
        try:
            digest = {str: str_digest, int: lambda x: x, float: float_digest,}[
                type(key)
            ](key)
        except KeyError:
            raise TypeError(f"Key {key} has unhashable type {type(key)}")

        idx = digest % self.bucket_count
        print(f"BUCKET: {idx} VALUE: {key}")
        self.buckets[idx].insert(key)

    def get(self, key) -> bool:
        try:
            digest = {str: str_digest, int: lambda x: x, float: float_digest,}[
                type(key)
            ](key)
        except KeyError:
            raise TypeError(f"Key {key} has unhashable type {type(key)}")
        idx = digest % self.bucket_count
        return self.buckets[idx][key] != None
