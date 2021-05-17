import 'package:cloud_firestore/cloud_firestore.dart';

class AttemptModel {
  final String id;
  final String photoUrl;
  final String userId;
  final DateTime createdAt;

  AttemptModel({this.id, this.photoUrl, this.userId, this.createdAt});

  AttemptModel.fromFirestoreDocument(QueryDocumentSnapshot document)
      : this.id = document.id,
        this.photoUrl = document['photoUrl'],
        this.userId = document.data()['userId'] ?? null,
        this.createdAt = DateTime.parse(document['createdAt']);
}
