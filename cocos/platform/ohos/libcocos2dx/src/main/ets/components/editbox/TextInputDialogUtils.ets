@CustomDialog
export struct TextInputDialog {
  showMessage: object = {message : ""}
  private isEditing: boolean = false
  accept: (msg: string) => void
  controller: CustomDialogController

  build() {
    Column() {
      Row() {
        TextInput({ text: this.showMessage["message"] })
          .backgroundColor('#ffffff')
          .layoutWeight(1)
          .caretColor(Color.Transparent)
          .onChange((value) => {
            this.showMessage["message"] = value
            if (this.accept) {
              this.accept(this.showMessage["message"])
            }
          })
          .onEditChange((isEditing) => {
            this.isEditing = isEditing
          })
          .onAppear(() => {

          })
          .onSubmit((value) => {
            if (this.accept) {
              this.accept(this.showMessage["message"])
            }
            this.controller.close()
          })
        Blank(8).width(16)
        Button('完成').onClick(() => {
          if (this.accept) {
            this.accept(this.showMessage["message"])
          }
          this.controller.close()
        })
      }.padding({ left: 8, right: 8, top: 8, bottom: 8 })
      .backgroundColor(Color.Gray)

    }
    .width('100%')

    .justifyContent(FlexAlign.End)
  }
}
