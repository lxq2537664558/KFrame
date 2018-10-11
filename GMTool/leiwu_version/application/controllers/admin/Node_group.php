<?php if ( ! defined('BASEPATH')) exit('No direct script access allowed');

class Node_group extends MY_Controller {

    public function __construct() {
        parent::__construct();//必须有
        $this->load->model('db_node_group');
    }

    function index() {
        $data['list'] = $this->db_node_group->listAll();//var_dump($data);
        $this->load->view('admin/node/group_list', $data);
    }

    //添加页
    public function add(){
        if($this->input->post()){
            $inAry = array(
                'name'=>trim($this->input->post('name')),
                'comment'=>trim($this->input->post('comment')),
                'add_user'=>$this->userData['uid'],
                'create_time'=>time(),
                'update_time'=>time(),
            );
            $res = $this->db_node_group->add($inAry);
            if($res){
                $dLogAry=['controller'=>__CLASS__,'action'=>__FUNCTION__,'type'=>1];
                $this->dbLog($dLogAry);
                $this->jsAlert('添加成功','/admin/node_group/index');
            }
        }
        $data['act']=0;
        $this->load->view('admin/node/add_node_group', $data);
    }

    //修改页
    public function modify($id){
        $data = $this->db_node_group->detail($id);
        $data['act']=1;

        if($this->input->post()){
            $upAry = array(
                'name'=>trim($this->input->post('name')),
                'comment'=>trim($this->input->post('comment')),
                'update_time'=>time(),
            );
            $res = $this->db_node_group->update($id,$upAry);
            if($res){
                $dLogAry=['controller'=>__CLASS__,'action'=>__FUNCTION__,'type'=>3];
                $this->dbLog($dLogAry);
                $logAry = array($id,$res,$this->userData['uid']);
                lwLog($logAry,'node_group_modify');
                $this->jsAlert('更新成功_'.$res,'/admin/node_group/index');
            }
        }
        $this->load->view('admin/node/add_node_group', $data);
    }

    //删除
    public function del($id){
        $res = $this->db_node_group->delete($id);
        if($res){
            $dLogAry=['controller'=>__CLASS__,'action'=>__FUNCTION__,'type'=>2];
            $this->dbLog($dLogAry);
            $logAry = array($id,$res,$this->userData['uid']);
            lwLog($logAry,__METHOD__);
            $this->jsAlert('删除成功_'.$res,'/admin/node_group/index');
        }
    }
}
