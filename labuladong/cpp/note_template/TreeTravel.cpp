void traverse(TreeNode root) {
    if (root == null) {
        return;
    }
    // 前序位置 code here
    traverse(root.left);
    // 中序位置 code here
    traverse(root.right);
    // 后序位置 code here
}