import 'dart:math';

import 'package:flutter/material.dart';
import 'package:get_it/get_it.dart';
import 'package:mobile/attempt/attempt.card.dart';
import 'package:mobile/attempt/attempt.model.dart';
import 'package:mobile/firestorage.service/firestorage.service.dart';
import 'package:mobile/firestore.service/firestore.service.dart';

class AttemptsTab extends StatefulWidget {
  @override
  State<StatefulWidget> createState() => _AttemptsTabState();
}

class _AttemptsTabState extends State<AttemptsTab> {
  final FirestoreService _firestoreService = GetIt.I.get<FirestoreService>();
  final FirestorageService _firestorageService =
      GetIt.I.get<FirestorageService>();
  List<AttemptModel> attempts = [];
  List<String> finalUrls = [];
  List<String> usernames = [];

  _AttemptsTabState() {
    _firestoreService.attempts.listen((value) {
      List<String> otherUrls = [];
      List<String> otherUsernames = [];
      value.forEach((e) async {
        String url =
            await _firestorageService.getAttemptPhotoByName(e.photoUrl);
        String name = (e.userId != null)
            ? (await _firestoreService.getUserById(e.userId))
            : 'Not recognized';
        otherUrls.add(url);
        otherUsernames.add(name);
      });
      setState(() {
        this.attempts = value;
        this.finalUrls = otherUrls;
        this.usernames = otherUsernames;
      });
      print('A ${attempts.length}');
      print('B ${finalUrls.length}');
      print('C ${usernames.length}');
    });
  }

  @override
  Widget build(BuildContext context) => Container(
        height: double.infinity,
        width: double.infinity,
        padding: EdgeInsets.all(10),
        child: ListView.separated(
          itemCount: this.attempts.length,
          physics: BouncingScrollPhysics(),
          itemBuilder: (BuildContext ctx, int idx) => AttemptCard(
            key: ObjectKey(this.attempts[idx].id),
            attemptModel: this.attempts[idx],
            finalPhotoUrl: this.finalUrls[idx],
            username: this.usernames[idx],
          ),
          separatorBuilder: (BuildContext ctx, int idx) => SizedBox(height: 20),
        ),
      );
}
