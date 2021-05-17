import 'package:cloud_firestore/cloud_firestore.dart';

class UserModel {
  final String id;
  final String photoUrl;
  final String name;
  final List<double> coordinates;
  final DateTime createdAt;

  UserModel(this.id, this.photoUrl, this.name)
      : this.coordinates = null,
        this.createdAt = DateTime.now();

  UserModel.fromFirestoreDocument(QueryDocumentSnapshot document)
      : this.id = document.id,
        this.coordinates = document['coordinates'] ?? [],
        this.photoUrl = document['photoUrl'],
        this.name = document['name'],
        this.createdAt = document.data().containsKey('createdAt')
            ? DateTime.fromMillisecondsSinceEpoch(document['createdAt'])
            : DateTime.now();

  Map<String, dynamic> toDict() {
    return {
      'photoUrl': this.photoUrl,
      'name': this.name,
      'createdAt': this.createdAt.millisecondsSinceEpoch,
      'coordinates': null
    };
  }
}
