import 'package:flutter/material.dart';

class AddUserCard extends StatelessWidget {
  @override
  Widget build(BuildContext context) => Container(
        height: 60,
        width: double.infinity,
        color: Colors.blue,
        alignment: Alignment.center,
        child: IconButton(
          icon: Icon(
            Icons.add,
            size: 30,
            color: Colors.white,
          ),
          onPressed: () => Navigator.of(context).pushNamed('/form'),
        ),
      );
}
