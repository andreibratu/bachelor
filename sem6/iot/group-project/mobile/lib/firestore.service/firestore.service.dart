import 'package:cloud_firestore/cloud_firestore.dart';
import 'package:mobile/attempt/attempt.model.dart';
import 'package:mobile/users/user.model.dart';
import 'package:rxdart/subjects.dart';

class FirestoreService {
  final BehaviorSubject<List<AttemptModel>> attempts;
  final BehaviorSubject<List<UserModel>> users;
  final FirebaseFirestore instance = FirebaseFirestore.instance;

  FirestoreService()
      : attempts = BehaviorSubject<List<AttemptModel>>(),
        users = BehaviorSubject<List<UserModel>>() {
    instance.collection('attempts').snapshots().listen((event) {
      List<AttemptModel> parsed =
          event.docs.map((e) => AttemptModel.fromFirestoreDocument(e)).toList();
      attempts.add(parsed);
    });
    instance.collection('users').snapshots().listen((event) {
      List<UserModel> parsed =
          event.docs.map((e) => UserModel.fromFirestoreDocument(e)).toList();
      users.add(parsed);
    });
  }

  addUser(UserModel user) async {
    await instance.collection('users').doc().set(user.toDict());
  }

  Future<UserModel> getUserById(String userId) async {
    DocumentSnapshot query =
        await instance.collection('users').doc(userId).get();
    return UserModel.fromFirestoreDocument(query);
  }
}
