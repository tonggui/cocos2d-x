import common from '@ohos.app.ability.common';

let implicitStartAbility = function (url: string) {
  let wantInfo = {
    'action': 'ohos.want.action.viewData',
    'uri': url
  }
  let context = globalThis.abilityContext as common.UIAbilityContext;
  context.startAbility(wantInfo).then(() => {
    console.log('[cocos] start ability!');

  }).catch((err) => {
    console.log('[cocos] start ability error!' + err);
  })
}
globalThis.wantUtils = {};
globalThis.wantUtils.implicitStartAbility = implicitStartAbility;