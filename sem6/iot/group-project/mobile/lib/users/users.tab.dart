import 'package:flutter/cupertino.dart';
import 'package:get_it/get_it.dart';
import 'package:mobile/firestore.service/firestore.service.dart';
import 'package:mobile/users/add.user.card.dart';
import 'package:mobile/users/user.card.dart';
import 'package:mobile/users/user.model.dart';

class UsersTab extends StatefulWidget {
  @override
  State<StatefulWidget> createState() => _UsersTabState();
}

class _UsersTabState extends State<UsersTab> {
  final FirestoreService _firestoreService = GetIt.I.get<FirestoreService>();
  List<UserModel> users = [];

  _UsersTabState() {
    _firestoreService.users.listen((value) {
      setState(() {
        this.users = value;
      });
    });
  }

  @override
  Widget build(BuildContext context) => Container(
        height: double.infinity,
        width: double.infinity,
        padding: EdgeInsets.all(10),
        child: ListView.separated(
          itemCount: users.length + 1,
          physics: BouncingScrollPhysics(),
          itemBuilder: (BuildContext ctx, int idx) => (idx == 0)
              ? AddUserCard()
              : UserCard(
                  key: ObjectKey(users[idx - 1].id),
                  userModel: users[idx - 1],
                ),
          separatorBuilder: (BuildContext ctx, int idx) => SizedBox(height: 20),
        ),
      );
}
