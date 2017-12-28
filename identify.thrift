service  FaceIdentify {
 void FI_add_face_database(1: string uid, 2: string user_info, 3: string group_id, 4: string imagename),
 i32 FI_del_face_database(1: string uid, 2: string group_id),
 i32 FI_update_face_database(1: string uid, 2: string user_info, 3: string group_id, 4: string imagename),
 i32 FI_find_user_info(1: string uid),
 string FI_find_group_users(1: string group_id),
 string FI_face_database_identify(1: string group_id, 2: string imagename),
 string FI_face_database_verify(1: string uid, 2: string user_info, 3: string group_id, 4: string imagename),
 i32 FI_group_deleteuser(1: string uid, 2: string group_id),
 i32 FI_group_adduser(1:string src_group_id, 2: string group_id, 3: string uid)
 string FI_face_detect(1:string imagename)
 string FI_face_match(1:string image1, 2:string image2)  
}


