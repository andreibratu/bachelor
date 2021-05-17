import 'dart:io';
import 'dart:math';

import 'package:firebase_storage/firebase_storage.dart' as firebase_storage;

class FirestorageService {
  final firebase_storage.FirebaseStorage storage =
      firebase_storage.FirebaseStorage.instance;
  final Random _rnd = Random();
  static final _chars =
      'AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz1234567890';

  String _getRandomString(int length) => String.fromCharCodes(Iterable.generate(
      length, (_) => _chars.codeUnitAt(_rnd.nextInt(_chars.length))));

  Future<String> uploadPhoto(File photo) async {
    String photoName = _getRandomString(32);
    await storage.ref('images/$photoName').putFile(photo);
    return storage.ref('images/$photoName').getDownloadURL();
  }

  Future<String> getAttemptPhotoByName(String name) async {
    return await storage.ref('attempts/$name.jpg').getDownloadURL();
  }
}
