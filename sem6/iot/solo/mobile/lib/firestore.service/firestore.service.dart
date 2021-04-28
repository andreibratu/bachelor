import 'dart:async';

import 'package:cloud_firestore/cloud_firestore.dart';
import 'package:mobile/keywords/keywords.model.dart';
import 'package:mobile/log/log.model.dart';
import 'package:rxdart/subjects.dart';

class FirestoreService {
  final BehaviorSubject<List<LogModel>> logs;
  final BehaviorSubject<List<KeywordModel>> keywords;
  final FirebaseFirestore instance = FirebaseFirestore.instance;

  FirestoreService()
      : logs = BehaviorSubject<List<LogModel>>(),
        keywords = BehaviorSubject<List<KeywordModel>>() {
    instance.collection('logs').snapshots().listen((event) {
      List<LogModel> parsed =
          event.docs.map((e) => LogModel.fromFirestoreDocument(e)).toList();
      logs.add(parsed);
    });
    instance.collection('keywords').snapshots().listen((event) {
      List<KeywordModel> parsed =
          event.docs.map((e) => KeywordModel.fromFirestoreDocument(e)).toList();
      keywords.add(parsed);
    });
  }

  void writeKeyword(String keyword) {
    instance.collection('keywords').add({'keyword': keyword, 'count': 0});
  }

  void deleteKeyword(String id) {
    instance.collection('keywords').doc(id).delete();
  }
}
