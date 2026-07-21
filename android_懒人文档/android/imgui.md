# imgui方法 (imgui)


## 1. imgui.addOptionItem(handle, item_text) : 添加选项

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | string | 是 | 选项框的句柄 |
| item_text | string | 是 | 选项项的文本 |


返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 无 | 无返回值 |

---

## 2. imgui.addRadioBox(handle, text, wrapline) : 添加单选框

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | string | 是 | 单选框的句柄 |
| text | string | 是 | 单选框的文本 |
| wrapline | boolean | 否 | 是否换行显示 |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 无 | 无返回值 |

---

## 3. imgui.addTabBarItem(tabBar_handle, title) : 向标签栏添加标签页

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| tabBar_handle | string | 是 | 标签栏的句柄 |
| title | string | 是 | 标签页的标题 |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 无 | 无返回值 |

---


## 4. imgui.clearTable(handle) : 清空表格所有行

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | string | 是 | 表格的句柄 |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 无 | 无返回值 |

---


## 5. imgui.close() : 关闭imgui框架

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | string | 是 | 弹窗的句柄 |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 无 | 无返回值 |

--- 

## 6. imgui.createBitmapShape(x,y,width,height,bitmap) : 创建位图形状

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| x | number | 是 | 位图形状的x坐标 |
| y | number | 是 | 位图形状的y坐标 |
| width | number | 是 | 位图形状的宽度 |
| height | number | 是 | 位图形状的高度 |
| bitmap | string | 是 | 位图的路径 |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 整数 | 位图形状的句柄 |

---

## 7. imgui.createButton(x,y,width,height,text) : 创建按钮

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| x | number | 是 | 按钮的x坐标 |
| y | number | 是 | 按钮的y坐标 |
| width | number | 是 | 按钮的宽度 |
| height | number | 是 | 按钮的高度 |
| text | string | 是 | 按钮的文本 |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 整数 | 新创建的按钮句柄 |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 按钮会继承父容器的布局方向 | 垂直/水平 |
| 当width/height为0时根据文本内容自动计算大小 | 无 |
| 当width/height为-1时填充满父容器可用空间 | 无 |
| 需要先创建有效的父容器| 无 |
| 按钮点击事件需通过setOnClick回调设置 | 无 |


---

## 8. imgui.createCheckBox(parent, label, checked) : 创建复选框

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| parent | string | 是 | 复选框的父容器句柄 |
| label | string | 是 | 复选框的标签文本 |
| checked | boolean | 否 | 是否默认选中 |

返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 整数 | 复选框控件句柄(>0的整数) |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 必须先调用imgui.isSupport()检查环境支持性 | 无 |
| 复选框会继承父容器的布局方向| 无 |
| 标签文本支持UTF-8编码 | 无 |
| 失败时应查询imgui.getLastError()获取详情 | 无 |


---

## 9. imgui.createColorPicker(parent, title, color, width, height) : 创建颜色选择器

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| parent | string | 是 | 父容器句柄 |
| title | string | 否 | 标题文本(默认"Color") |
| color | number | 否 | 初始颜色值(32位ARGB格式，默认0xFF000000) |
| width | number | 否 | 控件宽度(像素单位) |
| height | number | 否 | 控件高度(像素单位) |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 整数 | 颜色选择器句柄(成功) |
| nil | 失败(可通过imgui.getLastError()获取错误信息) |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 颜色格式为32位无符号整数 0xAARRGGBB | AA:透明度 RR:红色 GG:绿色 BB:蓝色 |
| 常用颜色示例:红色不透明0xFFFF0000 | 绿色半透明0x8000FF00 蓝色透明0x000000FF |
| 需先调用imgui.isSupport()检查环境支持性 | 无 |

---

## 10. imgui.setOnClick(buttonHandle, callback) : 设置按钮点击回调

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| buttonHandle | string | 是 | 按钮句柄(由createButton创建) |
| callback | function | 是 | 回调函数，格式为function(handle) |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 无 | 无返回值 |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 必须在按钮创建成功后调用 | 无 |
| 回调函数会在UI线程中执行，不宜做耗时操作 | 无 |
| 每个按钮只能设置一个点击回调，重复设置会覆盖之前的回调 | 无 |
| 如果需要在回调中修改UI元素，请使用imgui.post延迟处理 | 无 |
| 回调函数中不要直接销毁按钮本身 | 无 |

---

## 11. imgui.setOnCheck(handle, callback) : 设置复选框状态变更回调

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | string | 是 | 复选框控件句柄 |
| callback | function | 是 | 回调函数，格式为function(handle, state) |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 无 | 无返回值 |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| handle为复选框控件句柄 | state为当前选中状态(true/false) |
| 必须在复选框创建成功后调用 | 无 |

---

## 12. imgui.createSwitch(parent, label, checked, height) : 创建开关控件

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| parent | string | 是 | 父容器句柄(由createWindow等创建) |
| label | string | 是 | 开关右侧显示的文本 |
| checked | boolean | 否 | 初始状态(默认false) |
| height | number | 否 | 开关高度(不能为0) |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 整数 | 开关控件句柄(>0) |
| 0 | 创建失败(可通过imgui.getLastError()获取原因) |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 必须先调用imgui.isSupport()检查支持性 | 无 |
| 高度为0时根据系统DPI自动计算合适尺寸 | 无 |
| 文本支持多语言UTF-8编码 | 无 |
| 开关颜色可通过imgui.setStyleColor自定义 | 无 |

---

## 13. imgui.setChecked(handle, state) : 设置复选框/开关控件的选中状态

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | string | 是 | 复选框/开关控件句柄 |
| state | boolean | 是 | 要设置的选中状态 |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 无 | 无返回值 |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 需要确保句柄有效性 | 使用imgui.isValidHandle验证 |
| 线程安全，可在任意线程调用 | 无 |

---

## 14. imgui.isChecked(handle) : 获取复选框/开关控件的当前状态

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | string | 是 | 有效的控件句柄 |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| boolean | 当前选中状态(true表示选中/开启) |
| nil | 获取失败(句柄无效/控件类型不匹配) |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 返回值反映控件的实时状态(包含动画过渡中的状态) | 无 |
| 对已销毁的控件会返回nil | 无 |
| 线程安全，可在任何线程调用 | 无 |

---

## 15. imgui.createLabel(parent, text, singleline) : 创建文本标签

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| parent | string | 是 | 父容器句柄(由createWindow/createVerticalLayout等创建) |
| text | string | 是 | 要显示的文本内容 |
| singleline | boolean | 否 | 是否单行显示(默认true) |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 整数 | 标签控件句柄(>0) |
| 0 | 创建失败(使用imgui.getLastError()获取详情) |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 必须先调用imgui.isSupport()确认环境支持 | 无 |
| 文本内容支持UTF-8编码和转义字符(\n,\t等) | 无 |
| 多行模式下高度自动计算 | 无 |
| 可通过imgui.setWidgetText更新内容 | 无 |
| singleline为true时单行显示(超出部分截断) | false时多行显示(自动换行) |

---

## 16. imgui.createInputText(parent, label, value, inputType, width, height) : 创建输入框

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| parent | string | 是 | 父容器句柄 |
| label | string | 是 | 输入框左侧标签(支持HTML富文本) |
| value | string | 否 | 初始文本内容(默认为空字符串) |
| inputType | number | 否 | 输入类型(0:普通文本 1:密码 2:多行) |
| width | number | 否 | 控件宽度(像素，0表示自动计算) |
| height | number | 否 | 控件高度(像素，仅多行模式有效) |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 整数 | 输入框句柄(>0) |
| 0 | 创建失败(使用imgui.getLastError()获取原因) |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 多行模式需要显式设置高度(height≥60像素) | 无 |
| 密码输入框返回值是真实内容(非*号) | 无 |
| 输入类型不可运行时修改，需重新创建 | 无 |
| 使用imgui.inputSetMaskChar自定义密码掩码字符 | 无 |

---

## 17. imgui.getInputText(handle) : 获取输入框当前文本内容

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | string | 是 | 有效的输入框句柄(由createInputText创建) |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| string | 输入框当前文本内容 |
| nil | 获取失败(句柄无效/控件已销毁) |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 对于Password类型的输入框，返回的是真实内容而非掩码字符 | 无 |
| 多行文本会保留换行符(\n) | 无 |
| 线程安全，可在任何线程调用 | 无 |
| 对已销毁的输入框会返回nil | 无 |

---

## 18. imgui.setInputText(handle, text) : 设置输入框文本内容

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | string | 是 | 输入框控件句柄(由createInputText等函数创建) |
| text | string | 是 | 要设置的文本内容 |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 无 | 无返回值，失败时可通过imgui.getLastError()获取错误信息 |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 需要确保句柄有效性(使用imgui.isValidHandle验证) | 无 |
| 文本内容最大长度受系统限制(默认1024字符) | 无 |
| 支持包含转义字符(\n,\t等) | 单行输入框会自动过滤换行符 |
| 线程安全，可在任意线程调用 | 无 |
| 修改后会触发onInputChange事件 | 无 |
| 密码框类型会显示为掩码字符 | 无 |

---

## 19. imgui.setInputType(handle, inputType) : 设置输入框类型

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | string | 是 | 输入框控件句柄(由createInputField创建) |
| inputType | number | 是 | 输入类型(0:普通单行文本 1:密码输入 2:多行文本) |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 无 | 无返回值，失败时可通过imgui.getLastError()获取错误信息 |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 必须在创建输入框后调用 | 无 |
| 切换类型会清空现有内容 | 无 |
| 多行模式下会自动启用垂直滚动条 | 无 |
| 线程安全，可在任意线程调用 | 无 |

---

## 20. imgui.createProgressBar(parent, progress, width, height) : 创建水平进度条控件

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| parent | string | 是 | 父容器句柄 |
| progress | number | 是 | 初始进度值(0.0~1.0) |
| width | number | 否 | 进度条宽度(像素，0表示默认宽度) |
| height | number | 否 | 进度条高度(像素，0表示使用主题默认高度) |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 整数 | 进度条句柄(>0) |
| 0 | 创建失败(使用imgui.getLastError()获取原因) |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 进度值超过范围会自动钳制(小于0视为0，大于1视为1) | 无 |
| 修改进度需使用imgui.setProgress | 无 |
| 可通过imgui.setProgressColor自定义颜色 | 无 |
| 支持平滑动画过渡效果 | 无 |

---

## 21. imgui.setProgressBarPos(handle, progress) : 设置进度条当前进度值

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | string | 是 | 进度条控件句柄 |
| progress | number | 是 | 要设置的进度值(0.0~1.0) |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 无 | 无返回值 |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 进度值会立即生效 | 无 |
| 进度值超过范围会自动钳制 | 无 |

---

## 22. imgui.getProgressBarPos(handle) : 获取进度条当前进度值

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | string | 是 | 有效的进度条句柄 |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| number | 当前进度值(0.0~1.0范围的浮点数) |
| nil | 获取失败(句柄无效/控件已销毁) |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 返回值包含动画过渡中的中间值 | 无 |
| 对已销毁的进度条会返回nil | 无 |
| 线程安全，可在任何线程调用 | 无 |

---

## 23. imgui.createComboBox(parent_handle, items, width) : 创建组合框控件

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| parent_handle | string | 是 | 父控件句柄(窗口或容器控件) |
| items | string | 是 | 组合框选项内容，用竖线"|"分隔的字符串 |
| width | number | 否 | 控件宽度，0表示自动宽度(默认0) |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 整数 | 组合框控件句柄(>0) |
| 0 | 失败(可通过imgui.getLastError()获取错误信息) |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 需要确保父句柄有效性(使用imgui.isValidHandle验证) | 无 |
| 选项字符串最大长度受系统限制(默认2048字符) | 无 |
| 选项分隔符"|"会被自动转义，如需包含"|"字符需使用"\|" | 无 |
| 创建后可通过setComboBoxSelection设置选中项 | 无 |
| 控件高度由系统自动决定 | 无 |
| 选项变更会触发onComboBoxChange事件 | 无 |
| 线程安全，可在任意线程调用 | 无 |

---

## 24. imgui.getItemText(combo_handle, item_index) : 获取下拉项文本

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| combo_handle | string | 是 | 组合框控件句柄 |
| item_index | number | 是 | 要获取的项索引(从0开始) |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| string | 项文本字符串(成功) |
| nil | 失败 |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 索引超出范围将返回nil | 无 |
| 返回文本已自动处理转义字符 | 无 |
| 最大返回长度受系统限制(默认1024字符) | 无 |

---

## 25. imgui.removeItemAt(handle, item_index) : 删除组合框指定项

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | string | 是 | 组合框控件句柄 |
| item_index | number | 是 | 要删除的项索引(从0开始) |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 无 | 无返回值，失败时可通过imgui.getLastError()获取错误信息 |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 索引超出范围将不执行任何操作 | 无 |
| 删除后选中项会自动调整 | 无 |

---

## 26. imgui.removeAllItems(combo_handle) : 清空组合框所有项

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| combo_handle | string | 是 | 组合框控件句柄 |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 无 | 无返回值，失败时可通过imgui.getLastError()获取错误信息 |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 清空后选中索引将变为-1 | 无 |
| 性能优于循环调用removeItemAt | 无 |

---

## 27. imgui.getSelectedItemIndex(handle) : 获取组合框|表被选中的项

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | string | 是 | 组合框|表控件句柄 |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| number | 当前选中项的索引(从0开始) |
| -1 | 无选中项(组合框为空或未选择) |
| -2 | 函数执行出错(可通过imgui.getLastError()获取错误信息) |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 需要确保句柄有效性(使用imgui.isValidHandle验证) | 无 |
| ≥0表示有效选中索引 | -1表示无选中项 -2表示函数执行出错 |
| 与getComboBoxSelection功能相同，两者可互换使用 | 无 |
| 线程安全，可在任意线程调用 | 无 |

---

## 28. imgui.setItemSelected(handle, index) : 设置组合框|表选中项

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | string | 是 | 组合框|表控件句柄 |
| index | number | 是 | 要选中的项索引(从0开始) |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 无 | 无返回值，失败时可通过imgui.getLastError()获取错误信息 |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 索引超出范围将不执行任何操作 | 无 |

---

## 29. imgui.setOnSelectEvent(handle, callback) : 设置组合框/单选框选择事件回调

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | string | 是 | 控件句柄(由createComboBox或createRadioGroup创建) |
| callback | function | 是 | 回调函数，格式为function(handle, index, text) |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 无 | 无返回值，如果回调执行出错，错误信息会输出到stderr |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 重复设置会覆盖之前的回调 | 无 |
| 传入nil可移除现有回调 | 无 |
| 事件触发时机包括:用户选择新选项、通过程序调用setSelectedIndex改变选择 | 无 |
| 线程安全，回调在主UI线程执行 | 无 |
| 回调中应避免阻塞操作 | 无 |
| 对于单选框组，会传递当前选中项的索引和文本 | 无 |

---

## 30. imgui.createRadioGroup(parent, label) : 创建单选按钮组

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| parent | string | 是 | 父容器句柄(整数) |
| label | string | 是 | 单选组的标签文本(字符串) |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 整数 | 单选组的控件句柄(成功) |
| nil | 失败(可通过imgui.getLastError()获取错误信息) |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 需要使用imgui.addRadioBox向单选组添加选项 | 无 |
| 使用imgui.getSelectedRadio获取当前选中项 | 无 |

---

## 31. imgui.createTableView(parent, title, columns, showheader, width, height) : 创建表格视图

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| parent | string | 是 | 父容器句柄(整数) |
| title | string | 是 | 表格标题文本(字符串) |
| columns | number | 是 | 列数(整数) |
| showheader | boolean | 是 | 是否显示表头(布尔值) |
| width | number | 否 | 表格宽度(浮点数) |
| height | number | 否 | 表格高度(浮点数) |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 整数 | 表格的控件句柄(成功) |
| nil | 失败(可通过imgui.getLastError()获取错误信息) |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 列数必须大于0 | 无 |
| 宽度和高度为-1时使用默认大小 | 无 |

---

## 32. imgui.setTableHeaderItem(handle, col, text) : 设置表头文本

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | string | 是 | 表格句柄(整数) |
| col | number | 是 | 列索引(从0开始) |
| text | string | 是 | 表头文本(字符串) |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 无 | 无返回值，失败时可通过imgui.getLastError()获取错误信息 |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 列索引不能超过创建表格时指定的列数 | 无 |
| 如果表格设置为不显示表头(showheader=false)，设置的表头将不会显示 | 无 |

---

## 33. imgui.insertTableRow(handle, after) : 插入表格行

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | string | 是 | 表格句柄(整数) |
| after | number | 是 | 插入位置指示(整数) |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 整数 | 新插入行的索引(成功) |
| nil | 失败(可通过imgui.getLastError()获取错误信息) |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 行索引从0开始 | 无 |
| after=-1:在开头插入 after=-2:在末尾插入 after≥0:在指定行索引后插入 | 无 |
| 插入大量数据时建议先禁用表格刷新，完成后再启用 | 无 |

---

## 34. imgui.getTableItemText(handle, row, col) : 获取表格单元格文本

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | string | 是 | 表格句柄(由createTableView创建) |
| row | number | 是 | 行索引(从0开始) |
| col | number | 是 | 列索引(从0开始) |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 字符串 | 单元格文本内容(成功) |
| nil | 失败(可通过imgui.getLastError()获取错误信息) |
| 空字符串("") | 单元格为空 |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 行和列索引都不能超过表格当前的范围 | 无 |
| 返回的文本是原始内容，不包含任何格式化字符 | 无 |
| 批量获取数据时建议先获取行数再循环读取 | 无 |

---

## 35. imgui.getItemCount(handle) : 获取表格行数,或者组合框子项数，单选框控件子项数

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | string | 是 | 控件句柄(表格/组合框/单选框) |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 整数 | 控件项数(成功) |
| -1 | 失败(可通过imgui.getLastError()获取错误信息) |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 对于表格控件，返回行数 | 无 |
| 对于组合框控件，返回选项项数 | 无 |
| 对于单选框控件，返回单选选项数 | 无 |

---

## 36. imgui.setTableItemText(handle, row, col, text) : 设置表格单元格文本

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | string | 是 | 表格句柄(由createTableView创建) |
| row | number | 是 | 行索引(从0开始) |
| col | number | 是 | 列索引(从0开始) |
| text | string | 是 | 要设置的文本(字符串) |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 无 | 无返回值，失败时可通过imgui.getLastError()获取错误信息 |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 行和列索引都不能超过表格当前的范围 | 无 |

---

## 37. imgui.deleteTableRow(handle, row) : 删除表格行

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | string | 是 | 表格句柄(由createTableView创建) |
| row | number | 是 | 要删除的行索引(从0开始) |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 无 | 无返回值，失败时可通过imgui.getLastError()获取错误信息 |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 行索引必须有效(0到行数-1) | 无 |

---

## 38. imgui.setOnSelectEventEx(handle, callback) : 设置表格选择事件回调(扩展版)

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | string | 是 | 表格句柄(由createTableView创建) |
| callback | function | 是 | 回调函数，格式为function(handle, row, col, text) |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 无 | 无返回值，如果回调函数执行出错，错误信息会输出到stderr |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 重复设置会覆盖之前的回调 | 无 |
| 传入nil可移除现有回调 | 无 |
| 回调中不要进行耗时操作，以免阻塞UI线程 | 无 |
| 事件触发时机:当用户点击表格单元格时 | 无 |
| 线程安全，但回调会在主UI线程执行 | 无 |
| 回调函数内部错误不会影响程序继续运行 | 无 |

---

## 40. imgui.createSlider(parent, label, min, max, initialPos, width) : 创建滑动条控件

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| parent | string | 是 | 父容器句柄 |
| label | string | 是 | 滑动条标签文本 |
| min | number | 是 | 最小值(整数) |
| max | number | 是 | 最大值(整数) |
| initialPos | number | 是 | 初始位置(介于min和max之间) |
| width | number | 否 | 控件宽度(像素) |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 整数 | 滑动条句柄(成功) |
| nil | 失败(可通过imgui.getLastError()获取错误信息) |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| min必须小于max | 无 |
| initialPos必须在[min,max]范围内 | 无 |
| 宽度为-1时使用默认大小 | 无 |
| 会触发onControlCreate事件 | 无 |

---

## 41. imgui.setSlider(handle, pos) : 设置滑动条位置

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | string | 是 | 滑动条句柄 |
| pos | number | 是 | 要设置的位置值(整数) |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 无 | 无返回值，失败时可通过imgui.getLastError()获取错误信息 |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| pos必须在滑动条的[min,max]范围内 | 无 |
| 会触发onSliderChange事件 | 无 |
| 线程安全，可在任意线程调用 | 无 |

---

## 42. imgui.getSliderPos(handle) : 获取滑动条当前位置

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | string | 是 | 滑动条句柄 |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 整数 | 当前位置值(成功) |
| nil | 失败(可通过imgui.getLastError()获取错误信息) |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 返回值始终在[min,max]范围内 | 无 |
| 线程安全，可在任意线程调用 | 无 |
| 避免在频繁调用的循环中获取 | 无 |

---

## 43. imgui.setOnSliderEvent(handle, callback) : 设置滑动条值变化事件回调

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | string | 是 | 滑动条控件句柄(由createSlider创建) |
| callback | function | 是 | 回调函数，格式为function(handle, value) |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 无 | 无返回值，如果回调函数执行出错，错误信息会输出到stderr |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 事件触发时机:用户拖动滑块时实时触发、用户点击滑动条轨道跳转位置时、通过程序调用setSlider改变值时 | 无 |
| 重复设置会覆盖之前的回调 | 无 |
| 传入nil可移除现有回调 | 无 |
| 回调中不要进行耗时操作，以免阻塞UI线程 | 无 |
| 线程安全，但回调会在主UI线程执行 | 无 |
| 值变化频率可能很高，建议做适当节流处理 | 无 |

---

## 44. imgui.setWidgetSize(handle, width, height) : 设置控件尺寸

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | string | 是 | 控件句柄(整数) |
| width | number | 是 | 新的宽度值(浮点数，像素单位) |
| height | number | 是 | 新的高度值(浮点数，像素单位) |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 无 | 无返回值，失败时可通过imgui.getLastError()获取错误信息 |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 支持大多数可调整大小的控件(按钮、滑动条、文本框等) | 无 |
| width/height为-1:使用控件默认大小 | 无 |
| width/height为0:自动计算最小所需大小 | 无 |

---

## 45. imgui.createImage(parent, path, width, height) : 创建图片显示控件

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| parent | string | 是 | 父容器句柄(必须) |
| path | string | 否 | 图片文件路径(可选) |
| width | number | 否 | 图片显示宽度(可选，像素单位) |
| height | number | 否 | 图片显示高度(可选，像素单位) |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 整数 | 图片控件句柄(成功) |
| nil | 失败(可通过imgui.getLastError()获取错误信息) |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 路径是绝对路径 | 无 |
| 支持格式:PNG/JPG/BMP等系统支持的格式 | 无 |
| 传nil或不传创建空图片控件 | 无 |
| width/height为-1:铺满 | 无 |

---

## 46. imgui.setImage(handle, path) : 设置或更换显示图片

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | string | 是 | 图片控件句柄(必须) |
| path | string | 是 | 新图片文件路径 |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 无 | 无返回值，失败时可通过imgui.getLastError()获取错误信息 |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 传nil清空当前图片 | 无 |
| 支持格式同createImage | 无 |

---

## 47. imgui.setImageFromBitmap(handle, bitmap) : 设置图像对象

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | string | 是 | 图像控件句柄(整数) |
| bitmap | object | 是 | 位图对象(Java对象) |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 无 | 无返回值 |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| bitmap必须是有效的Java位图对象 | 无 |

---

## 48. imgui.setWidgetVisible(handle, visible) : 设置控件可见性

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | string | 是 | 控件句柄(整数) |
| visible | boolean | 是 | 可见性状态，true表示显示，false表示隐藏 |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 无 | 无返回值，失败时可通过imgui.getLastError()获取错误信息 |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 支持所有类型的控件 | 无 |

---

## 49. imgui.isWidgetVisible(handle) : 获取控件当前可见状态

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | string | 是 | 控件句柄(整数) |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| boolean | true表示控件可见，false表示控件隐藏 |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 返回控件当前的可见状态 | 无 |

---

## 50. imgui.setLayoutBorderVisible(handle, visible) : 设置容器布局控件是否显示边框

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | string | 是 | 控件句柄(整数) |
| visible | boolean | 是 | 可见性状态，true表示显示，false表示隐藏 |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 无 | 无返回值 |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 仅对容器布局控件有效 | 无 |

---

## 51. imgui.setWindowPos(handle, x, y) : 设置窗口位置

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | string | 是 | 布局容器句柄(整数) |
| x | number | 是 | 水平位置相对窗口左上角为原点(浮点数，像素单位) |
| y | number | 是 | 垂直位置相对窗口左上角为原点(浮点数，像素单位) |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 无 | 无返回值 |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 坐标原点为窗口左上角 | 无 |

---

## 52. imgui.setWindowSize(handle, width, height) : 设置窗口大小

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | string | 是 | 布局容器句柄(整数) |
| width | number | 是 | 宽 |
| height | number | 是 | 高 |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 无 | 无返回值 |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 设置窗口的宽度和高度 | 无 |

---

## 53. imgui.setWidgetStyle(handle, style, v1, v2) : 设置imgui控件一些属性

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | string | 是 | 布局容器句柄(整数) |
| style | number | 是 | ImGuiStyleVar类型 |
| v1 | number | 是 | 属性值 |
| v2 | number | 否 | 属性值(可选) |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 无 | 无返回值 |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| style参数为ImGuiStyleVar枚举类型 | 无 |
| 具体使用方式参考示例代码 | 无 |

---

## 54. imgui.setWidgetColor(handle, type, color) : 设置imgui控件的相关颜色

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | string | 是 | 布局容器句柄(整数) |
| type | number | 是 | ImGuiColor类型 |
| color | number | 是 | 颜色值整数类型 |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 无 | 无返回值 |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 所有颜色值使用0xAARRGGBB格式(Alpha,Red,Green,Blue) | 无 |
| Alpha值为00表示完全透明，FF表示完全不透明 | 无 |
| 颜色设置通常会影响所有同类型控件 | 无 |
| 建议在创建控件前设置颜色，以确保初始显示效果 | 无 |

---

## 55. imgui.setWindowFlags(handle, flags) : 设置窗口标志

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|
| handle | string | 是 | 布局容器句柄(整数) |
| flags | number | 是 | WindowFlags类型 |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 无 | 无返回值 |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| flags参数为WindowFlags枚举类型 | 无 |
| 支持单个标志或多个标志组合使用 | 无 |
| 常用标志包括NoTitleBar、NoResize、NoMove等 | 无 |
| 具体使用方式参考示例代码 | 无 |

---

## 56. imgui.createTabBar(parent_handle, title) : 创建标签栏控件

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| parent_handle | string | 是 | 父窗口或父控件句柄(整数) |
| title | string | 是 | 标签栏标题(字符串) |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 整数 | 标签栏句柄(成功) |
| nil | 失败(可通过imgui.getLastError()获取错误信息) |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 需要先创建父窗口/父控件 | 无 |
| 标签栏内部需要通过imgui.addTabBarItem()添加标签页 | 无 |

---

## 57. imgui.createRectangle(x, y, x1, y1, color, filled, rounding) : 创建矩形

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| x | number | 是 | 矩形左上角X坐标(数字) |
| y | number | 是 | 矩形左上角Y坐标(数字) |
| x1 | number | 是 | 矩形右下角X坐标(数字) |
| y1 | number | 是 | 矩形右下角Y坐标(数字) |
| color | number | 是 | 颜色值(十六进制整数，格式0xAARRGGBB) |
| filled | boolean | 是 | 是否填充(布尔值，true为填充，false为边框) |
| rounding | number | 是 | 圆角半径(数字，0为直角) |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 整数 | 矩形句柄(成功) |
| nil | 失败(可通过imgui.getLastError()获取错误信息) |

---

## 59. imgui.createCircle(x, y, radius, color, filled, segments) : 创建圆形

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| x | number | 是 | 圆心X坐标(数字) |
| y | number | 是 | 圆心Y坐标(数字) |
| radius | number | 是 | 半径(数字) |
| color | number | 是 | 颜色值(十六进制整数，格式0xAARRGGBB) |
| filled | boolean | 是 | 是否填充(布尔值) |
| segments | number | 是 | 分段数(整数，值越大圆越平滑) |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 整数 | 圆形句柄(成功) |
| nil | 失败(可通过imgui.getLastError()获取错误信息) |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 推荐分段数在12-64之间，平衡性能和质量 | 无 |
| 要绘制椭圆可以使用imgui.createEllipse() | 无 |

---

## 60. imgui.createPolygon(points, color, closed, filled, thickness) : 创建多边形

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| points | table | 是 | 顶点数组(table of x,y tables) |
| color | number | 是 | 颜色(0xAARRGGBB格式) |
| closed | boolean | 是 | 是否闭合(布尔值) |
| filled | boolean | 是 | 是否填充(布尔值) |
| thickness | number | 是 | 线宽(数字) |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 整数 | 图形句柄(成功) |
| nil | 失败 |

---

## 61. imgui.createLine(x1, y1, x2, y2, color, thickness) : 创建线段

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| x1 | number | 是 | 起点X坐标 |
| y1 | number | 是 | 起点Y坐标 |
| x2 | number | 是 | 终点X坐标 |
| y2 | number | 是 | 终点Y坐标 |
| color | number | 是 | 颜色值(0xAARRGGBB) |
| thickness | number | 是 | 线宽(像素) |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 整数 | 线段句柄 |

---

## 62. imgui.setShapePosition(handle, x, y) : 设置图形位置

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | string | 是 | 图形句柄 |
| x | number | 是 | 新坐标X(对于多边形是整体偏移) |
| y | number | 是 | 新坐标Y(对于多边形是整体偏移) |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 整数 | 0成功，-1失败 |

---

## 63. imgui.setShapeVisibility(handle, visible) : 设置图形可见性

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | string | 是 | 图形句柄 |
| visible | boolean | 是 | 是否可见(布尔值) |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 整数 | 0操作成功，-1操作失败 |

---

## 64. imgui.isShapeVisibility(handle) : 判断图形是否可见

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | string | 是 | 图形句柄 |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| boolean | true表示可见，false表示隐藏 |

---

## 65. imgui.createShapeText(x, y, w, h, text, text_color, bg_color, has_background, font_scale) : 创建文本图形

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| x | number | 是 | 位置坐标X |
| y | number | 是 | 位置坐标Y |
| w | number | 是 | 文本框宽度 |
| h | number | 是 | 文本框高度 |
| text | string | 是 | 文本内容(字符串) |
| text_color | number | 是 | 文字颜色(0xAARRGGBB) |
| bg_color | number | 是 | 背景颜色(0xAARRGGBB) |
| has_background | boolean | 是 | 是否显示背景(布尔值) |
| font_scale | number | 是 | 字体缩放系数(建议0.5~3.0) |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 整数 | 文本图形句柄 |

---

## 66. imgui.setShapeTextString(handle, new_text) : 修改文本内容

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | string | 是 | 文本图形句柄 |
| new_text | string | 是 | 新文本内容 |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| boolean | 是否修改成功 |

---

## 67. imgui.setShapeTextColor(handle, new_color) : 设置文本颜色

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | string | 是 | 文本图形句柄 |
| new_color | number | 是 | 新颜色(0xAARRGGBB) |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| boolean | 是否修改成功 |

---

## 68. imgui.setShapeTextBackground(handle, bg_color, has_bg) : 设置文本背景

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | string | 是 | 文本图形句柄 |
| bg_color | number | 是 | 背景颜色(0xAARRGGBB) |
| has_bg | boolean | 是 | 是否显示背景 |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| boolean | 是否修改成功 |

---

## 69. imgui.setShapeTextFontScale(handle, scale) : 设置文本图形字体缩放比例

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | string | 是 | 文本图形句柄(整数) |
| scale | number | 是 | 缩放比例(浮点数，建议范围0.5~3.0) |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| boolean | true设置成功，false设置失败(可通过imgui.getLastError()获取错误信息) |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 缩放后可能需要手动调整文本框尺寸 | 无 |
| 极端值可能导致文字渲染异常 | 无 |
| 缩放是相对于创建时的初始大小 | 无 |

---

## 70. imgui.removeShape(handle) : 删除图形对象

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | string | 是 | 要删除的图形句柄(整数) |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 整数 | 0删除成功，-1删除失败(无效句柄或已删除) |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 删除后句柄立即失效 | 无 |
| 建议在窗口关闭时批量删除所有图形 | 无 |
| 重复删除不会报错但返回-1 | 无 |

---

## 71. imgui.setBitmapShape(handle, bitmap) : 设置位图形状

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | string | 是 | 之前创建的位图形状句柄 |
| bitmap | object | 是 | 新的位图对象(Java对象) |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 无 | 无返回值 |

---

## 73. imgui.setShapeThickness(handle, thickness) : 设置形状边框厚度

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | string | 是 | 形状句柄(整数) |
| thickness | number | 是 | 边框厚度值(浮点数，必须大于0) |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| boolean | true表示设置成功，false表示失败 |

---

## 74. imgui.getWindowPos(windowHandle) : 获取窗口位置和尺寸

参数:


| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| windowHandle | string | 是 | 目标窗口的句柄(整数) |



返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| table | 成功时返回包含窗口位置和尺寸的表，结构为x,y,width,height |
| nil | 失败时返回nil |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 坐标系统以屏幕左上角为原点(0,0) | 无 |
| 所有尺寸单位为像素 | 无 |
| 需要确保传入的窗口句柄有效 | 无 |
| 如果窗口被最小化或隐藏，可能无法获取正确位置 | 无 |

---

## 75. imgui.isSupport() : 检测IMGUI支持状态

参数:

无参数

返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| boolean | true表示当前环境支持IMGUI |
| boolean | false表示当前环境不支持IMGUI |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 应在调用其他imgui函数前先检测支持情况 | 无 |
| 返回false时调用其他imgui函数可能产生未定义行为 | 无 |
| 典型不支持情况包括在不兼容的Android版本上运行 | 无 |
| 缺少必要的OpenGL ES3支持或系统内存不足 | 无 |

---

## 76. imgui.setColorTheme(style) : 设置imgui颜色主题

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| style | number | 是 | 1表示浅色主题，2表示经典主题，其它值表示黑色主题 |

返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| boolean | true表示当前环境支持IMGUI |
| boolean | false表示当前环境不支持IMGUI |

---

## 77. imgui.show([touchable], [font], [fontsize]) : 显示UI框架

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| touchable | boolean | 否 | 是否允许触摸交互，默认为true |
| font | string | 否 | 字体文件路径，默认为系统默认字体 |
| fontsize | number | 否 | 字体大小，默认为45.0 |

返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| boolean | true表示成功显示，false表示显示失败 |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 参数顺序不影响调用，函数会根据参数类型自动匹配 | 无 |
| 如果指定的字体文件不存在，将使用默认字体 | 无 |
| 重复参数类型会导致错误(例如传入两个数字参数) | 无 |
| 如果touchable为true，函数不返回直到imgui框架被关闭才会返回 | 无 |

---

## 78. imgui.showWindow(config) : 创建并显示独立窗口

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| config | table | 是 | 配置表，包含以下可选字段 |

配置表字段说明:
| 字段名 | 类型 | 必填 | 默认值 | 说明 |
|:---:|:---:|:---:|:---:|:---:|
| x | number | 否 | 0 | 窗口X坐标(整数) |
| y | number | 否 | 0 | 窗口Y坐标(整数) |
| width | number | 否 | 600 | 窗口宽度(整数) |
| height | number | 否 | 600 | 窗口高度(整数) |
| hastitle | boolean | 否 | true | 是否显示标题栏 |
| title | string | 否 | 无 | 窗口标题文本 |
| titlecolor | number | 否 | 0xFFFFFFFF | 标题文字颜色(ARGB格式) |
| titlebgcolor | number | 否 | 0xFF87CEFA | 标题栏背景色(ARGB格式) |
| hasclose | boolean | 否 | true | 是否显示关闭按钮 |
| closecolor | number | 否 | 0xFFFFFFFF | 关闭按钮颜色(ARGB格式) |
| hasresize | boolean | 否 | true | 是否显示设置窗口大小按钮 |
| resizecolor | number | 否 | 0xFFFFFFFF | 设置窗口大小按钮颜色(ARGB格式) |
| hastoggle | boolean | 否 | true | 是否显示窗口收缩按钮 |
| togglecolor | number | 否 | 0xFFFFFFFF | 设置窗口收缩按钮颜色(ARGB格式) |
| fontsize | number | 否 | 100 | 标题字体大小(整数) |

返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| boolean | true表示窗口创建成功，false表示失败 |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 这个方法和imgui.show不一样 | 无 |
| imgui.show是整个屏幕作为画布去渲染创建的窗口 | 无 |
| 这个函数是创建一个小的窗口作为画布去渲染imgui创建的窗口 | 无 |
| 默认第一个imgui的窗口是填充满你创建的窗口大小的 | 无 |

---

## 79. imgui.createWindow(title, x, y, width, height, showclose) : 创建一个imgui窗口

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| title | string | 是 | 窗口标题 |
| x | number | 是 | 窗口左上角相对屏幕的X坐标 |
| y | number | 是 | 窗口左上角相对屏幕的Y坐标 |
| width | number | 是 | 窗口的宽度 |
| height | number | 是 | 窗口的高度 |
| showclose | boolean | 是 | 是否显示关闭按钮 |

返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| string | 窗口的句柄 |

---

## 80. imgui.setOnClose(window_handle, callback_function) : 设置窗口关闭回调函数

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| window_handle | string | 是 | 窗口句柄 |
| callback_function | function | 是 | 回调函数 |

返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 无 | 无返回值 |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 回调函数接收窗口句柄作为参数 | 无 |
| 可以在回调中调用imgui.destroyWindow销毁窗口 | 无 |
| 返回false可以阻止关闭(需慎用) | 无 |

---

## 81. imgui.destroyWindow(handle) : 销毁一个imgui窗口

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | string | 是 | 要销毁的窗口句柄（由createWindow创建返回的值） |

返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| 无 | 无返回值 |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 销毁窗口后，对应的句柄将失效，不应再使用 | 无 |
| 建议在窗口关闭回调中使用此函数确保资源释放 | 无 |
| 重复销毁同一窗口可能导致错误 | 无 |

---

## 82. imgui.createVerticalLayout(parent, [width], [height]) : 创建垂直布局容器

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| parent | string | 是 | 父容器/窗口的句柄(整数) |
| width | number | 否 | 布局宽度(浮点数)，默认为0，值为-1时表示填满父容器宽度 |
| height | number | 否 | 布局高度(浮点数)，默认为0，值为-1时表示填满父容器高度 |

返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| string | 新创建的垂直布局句柄(整数) |
| string | 失败返回0 |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 子控件将按照添加顺序垂直排列 | 无 |
| 当width/height为0时使用自动计算大小 | 无 |
| 当width/height为-1时填充满父容器 | 无 |
| 必须先创建父容器再创建子布局 | 无 |

---

## 83. imgui.createHorticalLayout(parent, [width], [height]) : 创建水平布局容器

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| parent | string | 是 | 父容器/窗口的句柄(整数) |
| width | number | 否 | 布局宽度(浮点数)，默认为0，值为-1时表示填满父容器宽度 |
| height | number | 否 | 布局高度(浮点数)，默认为0，值为-1时表示填满父容器高度 |

返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| string | 新创建的水平布局句柄(整数) |
| string | 失败返回0 |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 子控件将按照添加顺序水平排列 | 无 |
| 当width/height为0时使用自动计算大小 | 无 |
| 当width/height为-1时填充满父容器 | 无 |
| 必须先创建父容器再创建子布局 | 无 |
| 注意函数名是HorticalLayout(不是Horizontal) | 无 |

---

## 84. imgui.createTreeBoxLayout(parent, title, width) : 创建树形布局容器

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| parent | string | 是 | 父容器句柄(整数) |
| title | string | 是 | 树形框标题文本(字符串) |
| width | number | 是 | 树形框宽度(浮点数，像素单位) |

返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| string | 成功返回树形框句柄(整数) |
| nil | 失败返回nil，可通过imgui.getLastError()获取错误信息 |

---

## 85. imgui.sameLine(handle, spacing) : 设置控件同行布局

参数:

| 参数名 | 类型 | 必填 | 说明 |
|:---:|:---:|:---:|:---:|
| handle | string | 是 | 控件句柄(整数) |
| spacing | number | 是 | 与前一个控件的间距(浮点数，像素单位) |

返回值:
| 返回值类型 | 说明 |
|:---:|:---:|
| boolean | 成功返回true |
| boolean | 失败返回false，可通过imgui.getLastError()获取错误信息 |

注意事项:
| 注意事项 | 说明 |
|:---:|:---:|
| 使当前控件与前一个控件在同一行显示 | 无 |
| spacing为-1表示系统计算 | 无 |

---


