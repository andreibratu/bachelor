import 'dart:io';

import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:get_it/get_it.dart';
import 'package:mobile/firestorage.service/firestorage.service.dart';
import 'package:mobile/firestore.service/firestore.service.dart';
import 'package:mobile/generic/image.source.overlay.dart';
import 'package:mobile/generic/loading/loading.overlay.dart';
import 'package:mobile/generic/pick.image.hint.dart';
import 'package:mobile/generic/unfocus.scaffold.dart';
import 'package:mobile/users/user.model.dart';

class FormScreen extends StatefulWidget {
  @override
  State<StatefulWidget> createState() => FormScreenState();
}

class FormScreenState extends State<FormScreen> {
  File pickedImage;
  var imagePickerOverlay;
  final nameController = TextEditingController();
  bool validForm = false;
  final FirestoreService _firestoreService = GetIt.I.get<FirestoreService>();
  final FirestorageService _firestorageService =
      GetIt.I.get<FirestorageService>();

  _validateForm() {
    setState(() {
      validForm = pickedImage != null && nameController.text.length != 0;
    });
  }

  _processForm() async {
    LoadingOverlay loadingOverlay = LoadingOverlay.show(context);
    String photoUrl = await _firestorageService.uploadPhoto(pickedImage);
    UserModel userModel = UserModel(null, photoUrl, nameController.text);
    await _firestoreService.addUser(userModel);
    loadingOverlay.dispose();
    Navigator.of(context).pop();
  }

  onSetOverlay(ImageSourceOverlay overlay) {
    this.imagePickerOverlay = overlay;
  }

  onImagePicked(File image) {
    setState(() {
      this.pickedImage = image;
    });
    _validateForm();
  }

  @override
  Widget build(BuildContext context) => UnfocusScaffold(
        body: SingleChildScrollView(
            child: Padding(
                padding: EdgeInsets.all(10),
                child: Column(
                  children: [
                    PickImageHint(
                        onImagePickedCallback: onImagePicked,
                        overlayLifecycleCallback: onSetOverlay,
                        backgroundImage: pickedImage,
                        height: MediaQuery.of(context).size.height * 0.5,
                        width: double.infinity),
                    SizedBox(
                      height: MediaQuery.of(context).size.height * 0.1,
                    ),
                    TextField(
                      controller: nameController,
                      onChanged: (_) => _validateForm(),
                      decoration: InputDecoration(
                          fillColor: Colors.blue,
                          focusColor: Colors.blue,
                          border: OutlineInputBorder(),
                          hintText: "User name"),
                    ),
                    SizedBox(
                      height: MediaQuery.of(context).size.height * 0.1,
                    ),
                    Container(
                      width: double.infinity,
                      height: 60,
                      child: ElevatedButton(
                        child: Text('Submit'),
                        onPressed: validForm ? _processForm : null,
                      ),
                    )
                  ],
                ))),
        appBar: AppBar(
          title: Text('Add User'),
        ),
      );
}
