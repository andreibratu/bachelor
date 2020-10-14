from bucket_list import BucketList
from digests import str_digest, float_digest


class HashTable:
    def __init__(self, bucket_count: int = 37):
        self.bucket_count = bucket_count
        self.buckets = [BucketList() for _ in range(bucket_count)]

    def __setitem__(self, key, val):
        try:
            digest = {str: str_digest, int: lambda x: x, float: float_digest,}[
                type(key)
            ](key)
        except KeyError:
            raise TypeError(f"Key {key} has unhashable type {type(key)}")

        idx = digest % self.bucket_count
        self.buckets[idx].insert((key, val))

    def __getitem__(self, key):
        try:
            digest = {str: str_digest, int: lambda x: x, float: float_digest,}[
                type(key)
            ](key)
        except KeyError:
            raise TypeError(f"Key {key} has unhashable type {type(key)}")
        idx = digest % self.bucket_count
        return self.buckets[idx][key]