import 'package:flutter/material.dart';
import 'package:mobile/generic/attribute.text.dart';
import 'package:mobile/users/user.model.dart';
import 'package:intl/intl.dart';

class UserCard extends StatelessWidget {
  final UserModel userModel;

  const UserCard({Key key, this.userModel}) : super(key: key);

  @override
  Widget build(BuildContext context) => Container(
      height: 300,
      width: double.infinity,
      alignment: Alignment.bottomCenter,
      decoration: BoxDecoration(
          image: DecorationImage(
              image: NetworkImage(userModel.photoUrl), fit: BoxFit.fill)),
      child: Container(
        color: Colors.blue.withOpacity(0.8),
        height: 60,
        width: double.infinity,
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            Padding(
                padding: EdgeInsets.all(5),
                child: AttributeText(
                  attributeName: 'Name',
                  attributeValue: '${userModel.name}',
                  textColor: Colors.white,
                )),
            Padding(
                padding: EdgeInsets.all(5),
                child: AttributeText(
                  attributeName: 'Created At',
                  attributeValue:
                      '${DateFormat('yyyy-MM-dd – kk:mm').format(userModel.createdAt)}',
                  textColor: Colors.white,
                )),
          ],
        ),
      ));
}
